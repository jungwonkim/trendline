#include "Sampler.h"
#include "Debug.h"
#include "Data.h"
#include "Platform.h"
#include "PMU.h"
#include "Printer.h"
#include "Timer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>

namespace trendline {

Sampler::Sampler(int cpu, int* events, int freq) {
  cpu_ = cpu;
  nevents_ = 0;
  for (int i = 0; i < Platform::GetPlatform()->pmu()->ncounters(); i++) {
    if (events[i] < 0) break;
    events_[i] = events[i];
    nevents_++;
  }
  freq_ = freq;

  data_ = new Data();
  timer_ = Platform::GetPlatform()->timer();
  Init();
}

Sampler::~Sampler() {
  for (int i = 0; i < nevents_; i++) {
    if (fd_[i] != -1) close(fd_[i]);
  }
  delete data_;
}

int Sampler::Init() {
  memset(attr_, 0, nevents_ * sizeof(attr_[0]));
  for (int i = 0; i < nevents_; i++) {
    attr_[i].size = sizeof(struct perf_event_attr);
    attr_[i].inherit = 1;
    attr_[i].disabled = 0;
    attr_[i].exclude_kernel = 1;
    attr_[i].exclude_hv = 1;
    attr_[i].read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    attr_[i].type = PERF_TYPE_RAW;
    attr_[i].config = events_[i];

    int lead = i == 0 ? -1 : fd_[0];
    fd_[i] = syscall(__NR_perf_event_open, attr_ + i, 0, cpu_, lead, 0); 
    if (fd_[i] == -1) {
      perror("syscall");
      _error("event[%d] config[0x%llx]", i, attr_[i].config);
    }
    ioctl(fd_[i], PERF_EVENT_IOC_ID, id_ + i);
  }
  return TRENDLINE_OK;
}

void Sampler::Run() {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu_, &cpuset);
  if (pthread_setaffinity_np(thread_, sizeof(cpuset), &cpuset) != 0)
    _error("cpu[%d]", cpu_);

  Reset();

  do {
    usleep(1000 * 1000 / freq_);
    Sample();
  } while (running_);
}

int Sampler::Reset() {
  if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
    perror("ioctl");
    return TRENDLINE_ERR;
  }
  if (ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
    perror("ioctl");
    return TRENDLINE_ERR;
  }
  return TRENDLINE_OK;
}

int Sampler::Sample() {
  if (ioctl(fd_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");

  struct read_format cnt;
  if (read(fd_[0], &cnt, sizeof(cnt)) < 0) return TRENDLINE_ERR;

  data_->AddTime(timer_->Now());
  for (u_int64_t i = 0; i < cnt.nr; i++) {
    //if (id_[i] != cnt.values[i].id) _error("id[%llu] vs read_id[%llu]", id_[i], cnt.values[i].id);
    data_->AddCount(i, cnt.values[i].value);
  }
  data_->Commit();

  Reset();

  return TRENDLINE_OK;
}

} /* namespace trendline */
