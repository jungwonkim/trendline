#ifndef TRENDLINE_SRC_PMU_NEOVERSE_N1_H
#define TRENDLINE_SRC_PMU_NEOVERSE_N1_H

#include "PMU.h"
#include <map>

namespace trendline {

class PMUNeoverseN1 : public PMU {
public:
  PMUNeoverseN1();
  ~PMUNeoverseN1();

  virtual int InitS2E();

  virtual int* Events(int i);
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_PMU_NEOVERSE_N1_H */
