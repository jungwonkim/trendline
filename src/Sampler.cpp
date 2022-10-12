#include "Sampler.h"
#include "Debug.h"
#include "Data.h"
#include "Platform.h"
#include "Printer.h"
#include "Timer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>

namespace yamp {

Sampler::Sampler(int cpu, int* events, int freq, int start) {
  cpu_ = cpu;
  nevents_ = 0;
  for (int i = 0; i < YAMP_MAX_EVENTS; i++) {
    if (events[i] < 0) break;
    events_[i] = events[i];
    nevents_++;
  }
  freq_ = freq;
  start_ = start;
  pid_ = -1;

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
      _error("event[%d] config[0x%x]", i, attr_[i].config);
    }
    ioctl(fd_[i], PERF_EVENT_IOC_ID, id_ + i);
  }
  return YAMP_OK;
}

int Sampler::InitParams() {
#if 0
  const char* env = getenv("YAMP_EVENTS");
  char str[256];
  if (env) strncpy(str, env, strlen(env) + 1);
  else strncpy(str, YAMP_DEFAULT_EVENTS, strlen(YAMP_DEFAULT_EVENTS) + 1);

  char* rest = str;
  char* a = NULL;
  while ((a = strtok_r(rest, ",", &rest))) {
    attr_[nevents_].config = (int) strtol(a, NULL, 16);
    nevents_++;
    if (nevents_ >= YAMP_MAX_EVENTS) break;
  }

  _info("cpu[%d] freq[%d] nevents[%d]", cpu_, freq_, nevents_);
#endif
  return YAMP_OK;
}

void Sampler::Run() {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(cpu_, &cpuset);
  if (pthread_setaffinity_np(thread_, sizeof(cpuset), &cpuset) != 0)
    _error("cpu[%d]", cpu_);

  if (start_ > 0) sleep(start_);
  if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");
  if (ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");
  do {
    usleep(1000 * 1000 / freq_);
    Sample();
  } while (running_);
}

int Sampler::Sample() {
  if (ioctl(fd_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");

  struct read_format cnt;
  ssize_t s = read(fd_[0], &cnt, sizeof(cnt));

  data_->AddTime(timer_->Now());
  for (int i = 0; i < cnt.nr; i++) {
    if (id_[i] != cnt.values[i].id) _error("id[%llu] vs read_id[%llu]", id_[i], cnt.values[i].id);
    data_->AddCount(i, cnt.values[i].value);
  }
  data_->Commit();

  if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");
  if (ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");

  return YAMP_OK;
}

} /* namespace yamp */
