#include "Printer.h"
#include "Sampler.h"
#include "Type.h"
#include "Debug.h"
#include "Data.h"
#include "Platform.h"
#include "PMU.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace yamp {

Printer::Printer(Sampler* sampler) {
  sampler_ = sampler;
  pmu_ = Platform::GetPlatform()->pmu();
}

Printer::~Printer() {

}

int Printer::Print(Data* data) {
  FILE* fp = stderr;
  if (Platform::GetPlatform()->csv()) {
    char filename[256];
    sprintf(filename, YAMP_LOG_FILENAME, Platform::GetPlatform()->sid());
    fp = fopen(filename, "a");
  }

  nevents_ = sampler_->nevents();
  fprintf(fp, "TIME(CPU%d)", sampler_->cpu());
  for(int i = 0; i < nevents_; i++) {
    fprintf(fp, ",%s", pmu_->String(sampler_->event(i)));
  }
  fprintf(fp, "\n");

  yamp_row* rows = data->rows();
  for (int i = 0; i < data->nrows(); i++) {
    fprintf(fp, "%.5f", rows[i].time);
    for (int j = 0; j < nevents_; j++) {
      fprintf(fp, ",%lld", rows[i].data[j]);
    }
    fprintf(fp, "\n");
  }

  fflush(fp);

  if (fp != stderr) fclose(fp);

  return YAMP_OK;
}

} /* namespace yamp */

