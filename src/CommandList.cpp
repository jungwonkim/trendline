#include "CommandList.h"
#include "Debug.h"
#include "PMU.h"
#include "Platform.h"

namespace trendline {

CommandList::CommandList(int argc, char** argv) : Command(argc, argv) {
  fp_ = stderr;
  pmu_ = Platform::GetPlatform()->pmu();
}

CommandList::~CommandList() {
  if (fp_ != stderr) fclose(fp_);
}

int CommandList::Init() {
  return TRENDLINE_OK;
}

int CommandList::Run() {
  int ncounters = pmu_->ncounters();
  int ngroups = pmu_->ngroups();
  for (int i = 0; i < ngroups; i++) {
    fprintf(fp_, "GROUP%3d:", i);
    int* events = pmu_->Events(i);
    for (int j = 0; j < ncounters; j++) {
      int e = events[j];
      if (e < 0) break;
      fprintf(fp_, " %s,", pmu_->String(e));
    }
    fprintf(fp_, "\n");
  }
  return TRENDLINE_OK;
}

} /* namespace trendline */
