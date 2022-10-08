#ifndef YAMP_SRC_PMU_H
#define YAMP_SRC_PMU_H

#include "Type.h"

namespace yamp {

class PMU {
public:
  PMU();
  ~PMU();

  const char* String(int event);

  int* Events(int i) { return events_[i]; }

private:
  int (*events_)[YAMP_MAX_EVENTS];
};

} /* namespace yamp */

#endif /* YAMP_SRC_PMU_H */
