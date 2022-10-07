#ifndef YAMP_SRC_SAMPLER_H
#define YAMP_SRC_SAMPLER_H

#include "Type.h"
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
class Printer;
class Timer;

class Sampler {
public:
  Sampler();
  ~Sampler();

  int Run(char** argv);
  int Init();
  int Sample();
  int Print();

  int freq() { return freq_; }
  int cpu() { return cpu_; }
  int nevents() { return nevents_; }
  int event(int i) { return event_[i].config; }
  bool log() { return log_; }

private:
  int InitParams();

private:
  int freq_;
  int cpu_;
  int nevents_;
  bool log_;
  struct perf_event_attr event_[YAMP_MAX_EVENTS];
  int fd_[YAMP_MAX_EVENTS];
  u_int64_t id_[YAMP_MAX_EVENTS];
  struct read_format cnt_;

  Data* data_;
  Printer* printer_;
  Timer* timer_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_SAMPLER_H */
