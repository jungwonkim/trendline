#include "Timer.h"
#include <time.h>

namespace yamp {

Timer::Timer() {
  boot_ = 0.0;
  boot_ = Now();
}

Timer::~Timer() {

}

double Timer::Now() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return t.tv_sec + 1.e-9 * t.tv_nsec - boot_;
}

} /* namespace yamp */
