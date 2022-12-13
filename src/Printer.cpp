#include "Printer.h"
#include "Sampler.h"
#include "Debug.h"
#include "Data.h"
#include "Platform.h"
#include "PMU.h"
#include "Timer.h"
#include <time.h>
#include <unistd.h>
#include <ctime>

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

int Printer::PrintBootTime(FILE* fp) {
  double boot = Platform::GetPlatform()->timer()->boot();
  time_t secs = (time_t) boot;
  fprintf(fp, "Boot time: %.9lf, %s", Platform::GetPlatform()->timer()->boot(), std::asctime(std::localtime(&secs)));
  fflush(fp);
  return TRENDLINE_OK;
}


} /* namespace trendline */

