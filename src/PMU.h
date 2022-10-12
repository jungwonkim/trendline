#ifndef TRENDLINE_SRC_PMU_H
#define TRENDLINE_SRC_PMU_H

#include "Type.h"

namespace trendline {

class PMU {
public:
  PMU();
  ~PMU();

  const char* String(int event);

  int* Events(int i) { return events_[i]; }

private:
  int (*events_)[TRENDLINE_MAX_EVENTS];
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_PMU_H */
