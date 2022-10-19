#ifndef TRENDLINE_SRC_PMU_H
#define TRENDLINE_SRC_PMU_H

#include "Config.h"
#include <map>
#include <string>

#define S2E(e)              s2e_[#e] = e

namespace trendline {

class PMU {
public:
  PMU();
  virtual ~PMU();

  const char* String(int event);
  int Event(const char* string);

  int ncounters() { return ncounters_; }
  int ngroups() { return ngroups_; }

public:
  virtual int* Events(int i) = 0;

protected:
  virtual int InitS2E() = 0;
  int InitE2S();

public:
  static PMU* GetPMU();

private:
  static PMU* GetICX();
  static PMU* GetNeoverseV1();

protected:
  int ncounters_;
  int ngroups_;
  int *events_;

  std::map<int, std::string> e2s_;
  std::map<std::string, int> s2e_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_PMU_H */
