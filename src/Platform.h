#ifndef YAMP_SRC_PLATFORM_H
#define YAMP_SRC_PLATFORM_H

#include "Type.h"

namespace yamp {

class Sampler;
class Timer;
class PMU;

class Platform {
private:
  Platform();
  ~Platform();

public:
  int Init(int* argc, char*** argv);
  int Finalize();
  int Run();

  int sid() { return sid_; }
  PMU* pmu() { return pmu_; }
  Timer* timer() { return timer_; }

  bool csv() { return csv_; }
  double Now();

public:
  static Platform* GetPlatform();

private:
  int SetSID();
  int InitEventsSet();
  int GetOptions();

private:
  int* argc_;
  int cmd_;
  char*** argv_;
  bool init_;
  bool finalize_;
  bool csv_;
  int freq_;
  int start_;
  int ncpus_;
  int nsamplers_;
  int sid_;

  Sampler* samplers_[YAMP_MAX_EVENTS_SET];

  PMU* pmu_;
  Timer* timer_;

private:
  static Platform* singleton_;

};

} /* namespace yamp */

#endif /* YAMP_SRC_PLATFORM_H */
