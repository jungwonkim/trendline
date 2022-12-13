#include "Timer.h"
#include <time.h>

namespace trendline {

Timer::Timer() {
  Reset();
}

Timer::~Timer() {

}

void Timer::Reset() {
  boot_ = 0.0;
  boot_ = Now();
}

double Timer::Now() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return t.tv_sec + 1.e-9 * t.tv_nsec - boot_;
}

} /* namespace trendline */
