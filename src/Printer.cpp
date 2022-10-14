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

namespace trendline {

Printer::Printer(FILE* fp) {
  fp_ = fp;
  pmu_ = Platform::GetPlatform()->pmu();
}

Printer::~Printer() {

}

int Printer::Print(Sampler* sampler) {
  int nevents = sampler->nevents();
  Data* data = sampler->data();

  fprintf(fp_, "TIME(CPU%d)", sampler->cpu());
  for(int i = 0; i < nevents; i++) {
    fprintf(fp_, ",%s", pmu_->String(sampler->event(i)));
  }
  fprintf(fp_, "\n");

  trendline_row* rows = data->rows();
  for (int i = 0; i < data->nrows(); i++) {
    fprintf(fp_, "%.5f", rows[i].time);
    for (int j = 0; j < nevents; j++) {
      fprintf(fp_, ",%lu", rows[i].data[j]);
    }
    fprintf(fp_, "\n");
  }

  fflush(fp_);

  return TRENDLINE_OK;
}

} /* namespace trendline */

