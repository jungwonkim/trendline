#ifndef TRENDLINE_SRC_PMU_ICX_H
#define TRENDLINE_SRC_PMU_ICX_H

#include "PMU.h"
#include <map>

namespace trendline {

class PMUICX : public PMU {
public:
  PMUICX();
  ~PMUICX();

  virtual int InitS2E();

  virtual int* Events(int i);
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_PMU_ICX_H */
