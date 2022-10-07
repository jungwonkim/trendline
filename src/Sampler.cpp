#include "Sampler.h"
#include "Debug.h"
#include "Data.h"
#include "Printer.h"
#include "Timer.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/wait.h>

#define YAMP_DEFAULT_CPU    -1
#define YAMP_DEFAULT_FREQ   10
#define YAMP_DEFAULT_EVENTS "11,1b,3e,3d,3b,3a"

namespace yamp {

Sampler::Sampler() {
  nevents_ = 0;
  data_ = new Data();
  printer_ = new Printer(this);
  timer_ = new Timer();
  Init();
}

Sampler::~Sampler() {
  for (int i = 0; i < nevents_; i++) {
    if (fd_[i] != -1) close(fd_[i]);
  }
  delete printer_;
  delete data_;
  delete timer_;
}

int Sampler::Init() {
  memset(event_, 0, sizeof(event_));
  for (int i = 0; i < YAMP_MAX_EVENTS; i++) {
    event_[i].inherit = 1;
    event_[i].disabled = 0;
    event_[i].exclude_kernel = 1;
    event_[i].exclude_hv = 1;
    event_[i].read_format = PERF_FORMAT_GROUP | PERF_FORMAT_ID;
    event_[i].type = PERF_TYPE_RAW;
  }
  InitParams();

  for (int i = 0; i < nevents_; i++) {
    int parent = i == 0 ? -1 : fd_[0];
    fd_[i] = syscall(__NR_perf_event_open, event_ + i, 0, cpu_, parent, 0); 
    if (fd_[i] == -1) {
      perror("syscall");
      _error("event[%d] config[0x%x]", i, event_[i].config);
    }
    ioctl(fd_[i], PERF_EVENT_IOC_ID, id_ + i);
  }
  return YAMP_OK;
}

int Sampler::InitParams() {
  const char* env = getenv("YAMP_FREQ");
  freq_ = env ? atoi(env) : YAMP_DEFAULT_FREQ;

  env = getenv("YAMP_CPU");
  cpu_ = env ? atoi(env) : YAMP_DEFAULT_CPU;

  env = getenv("YAMP_EVENTS");
  char str[256];
  if (env) strncpy(str, env, strlen(env) + 1);
  else strncpy(str, YAMP_DEFAULT_EVENTS, strlen(YAMP_DEFAULT_EVENTS) + 1);

  char* rest = str;
  char* a = NULL;
  while ((a = strtok_r(rest, ",", &rest))) {
    event_[nevents_].config = (int) strtol(a, NULL, 16);
    nevents_++;
    if (nevents_ >= YAMP_MAX_EVENTS) break;
  }

  _info("cpu[%d] freq[%d] nevents[%d]", cpu_, freq_, nevents_);
  return YAMP_OK;
}

int Sampler::Run(char** argv) {
  if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");
  if (ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");

  pid_t p = fork();
  if (p == 0)
    if (execvp(argv[1], argv + 1) == -1) _error("%s", argv[1]);

  int status;
  do {
    usleep(1000 * 1000 / freq_);
    Sample();
    int child = waitpid(p, &status, WNOHANG);
    if (WIFEXITED(status) && child > 0) break;
  } while (true);

  return YAMP_OK;
}

int Sampler::Sample() {
  if (ioctl(fd_[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");

  struct read_format cnt_;
  read(fd_[0], &cnt_, sizeof(cnt_));

  data_->NewEpoch(timer_->Now());
  for (int i = 0; i < cnt_.nr; i++) {
    data_->AddCount(i, cnt_.values[i].value);
  }
  data_->Commit();

  if (ioctl(fd_[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");
  if (ioctl(fd_[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) perror("ioctl");

  return YAMP_OK;
}

int Sampler::Print() {
  return printer_->Print(data_);
}

} /* namespace yamp */
