#ifndef TRENDLINE_SRC_TIMER_H
#define TRENDLINE_SRC_TIMER_H

namespace trendline {

class Timer {
public:
  Timer();
  ~Timer();

  double boot() { return boot_; }

  void Reset();
  double Now();

private:
  double boot_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_TIMER_H */

