#ifndef YAMP_SRC_SAMPLER_H
#define YAMP_SRC_SAMPLER_H

#include "Type.h"
#include "Thread.h"
#include <linux/perf_event.h>

struct read_format {
  u_int64_t nr;
  struct {
    u_int64_t value;
    u_int64_t id;
  } values[YAMP_MAX_EVENTS];
};

namespace yamp {

class Data;
class Timer;

class Sampler : public Thread {
public:
  Sampler(int cpu, int* events, int freq, int start);
  virtual ~Sampler();

  virtual void Run();
  int Init();
  int Sample();
  int Print();

  Data* data() { return data_; }
  int cpu() { return cpu_; }
  int nevents() { return nevents_; }
  int event(int i) { return events_[i]; }
  int freq() { return freq_; }

  void set_pid(pid_t pid) { pid_ = pid; }

private:
  int InitParams();

private:
  int cpu_;
  int events_[YAMP_MAX_EVENTS];
  int nevents_;
  int freq_;
  int start_;
  struct perf_event_attr attr_[YAMP_MAX_EVENTS];
  int fd_[YAMP_MAX_EVENTS];
  u_int64_t id_[YAMP_MAX_EVENTS];

  pid_t pid_;

  Data* data_;
  Timer* timer_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_SAMPLER_H */
