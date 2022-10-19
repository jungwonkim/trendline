#include "PMU.h"
#include "Debug.h"
#include "PMUICX.h"
#include "PMUNeoverseV1.h"

namespace trendline {

PMU::PMU() {
}

PMU::~PMU() {
  if (events_) delete[] events_;
}

int PMU::InitE2S() {
  for (std::map<std::string, int>::iterator I = s2e_.begin(), E = s2e_.end(); I != E; ++I) {
    std::string s = (std::string) I->first;
    int e = (int) I->second;
    if (e2s_.count(e) > 0) _error("already key[%s]->[%x]", s.c_str(), e);
    else e2s_[e] = s;
  }
  return TRENDLINE_OK;
}

const char* PMU::String(int event) {
  if (e2s_.count(event) < 1) return NULL;
  return e2s_[event].c_str();
}

int PMU::Event(const char* string) {
  if (s2e_.count(string) < 1) return -1;
  return s2e_[string];
}

PMU* PMU::GetPMU() {
  PMU* pmu = NULL;
  FILE* fp = fopen("/proc/cpuinfo", "rb");
  char* line = 0;
  size_t size = 0ULL;
  while (getdelim(&line, &size, 0, fp) != -1) {
    if (strstr(line, "Intel")) {
      pmu = GetICX();
      break;
    }
    if (strstr(line, "0xd40")) {
      pmu = GetNeoverseV1();
      break;
    }
  }
  free(line);
  fclose(fp);
  return pmu; 
}

PMU* PMU::GetICX() {
  return new PMUICX();
}

PMU* PMU::GetNeoverseV1() {
  return new PMUNeoverseV1();
}

} /* namespace trendline */
