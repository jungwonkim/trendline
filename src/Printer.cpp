#include "Printer.h"
#include "Sampler.h"
#include "Type.h"
#include "Debug.h"
#include "Data.h"
#include "Platform.h"
#include "PMU.h"
#include <unistd.h>

namespace trendline {

Printer::Printer() {
  pmu_ = Platform::GetPlatform()->pmu();
}

Printer::~Printer() {

}

int Printer::Print(FILE* fp, Sampler* sampler) {
  int nevents = sampler->nevents();
  Data* data = sampler->data();

  fprintf(fp, "TIME(CPU%d)", sampler->cpu());
  for(int i = 0; i < nevents; i++) {
    fprintf(fp, ",%s", pmu_->String(sampler->event(i)));
  }
  fprintf(fp, "\n");

  trendline_row* rows = data->rows();
  for (int i = 0; i < data->nrows(); i++) {
    fprintf(fp, "%.5f", rows[i].time);
    for (int j = 0; j < nevents; j++) {
      fprintf(fp, ",%lu", rows[i].data[j]);
    }
    fprintf(fp, "\n");
  }

  fflush(fp);

  return TRENDLINE_OK;
}

} /* namespace trendline */

