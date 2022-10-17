#ifndef TRENDLINE_SRC_PMU_NEOVERSE_V1_H
#define TRENDLINE_SRC_PMU_NEOVERSE_V1_H

#include "PMU.h"
#include <map>

namespace trendline {

class PMUNeoverseV1 : public PMU {
public:
  PMUNeoverseV1();
  ~PMUNeoverseV1();

  virtual int InitS2E();

  virtual int* Events(int i);
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_PMU_NEOVERSE_V1_H */
