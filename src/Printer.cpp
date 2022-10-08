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
  FILE* fp = stdout;
  if (false) {
    char filename[256];
    for (int i = 0; i < 9999; i++) {
      sprintf(filename, "yamp-%04d.log", i);
      if (access(filename, F_OK) != 0) break;
    }
    fp = fopen(filename, "w");
  }

  nevents_ = sampler_->nevents();
  fprintf(fp, "%s", "TIME");
  for(int i = 0; i < nevents_; i++) {
    //fprintf(fp, "%12p", sampler_->event(i));
    fprintf(fp, ",%s", pmu_->String(sampler_->event(i)));
  }
  fprintf(fp, "\n");

  int nrows = data->nrows();
  yamp_row* chunk = data->current();
  for (int j = 0; j < nrows; j++) {
    fprintf(fp, "%.3f", chunk[j].time);
    for (int k = 0; k < nevents_; k++) {
      fprintf(fp, ",%lld", chunk[j].data[k]);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);

  return YAMP_OK;
}

} /* namespace yamp */

