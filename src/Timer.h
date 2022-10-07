#ifndef YAMP_SRC_TIMER_H
#define YAMP_SRC_TIMER_H

#include <stddef.h>

namespace yamp {

class Timer {
public:
  Timer();
  ~Timer();

  double Now();

private:
  double boot_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_TIMER_H */

