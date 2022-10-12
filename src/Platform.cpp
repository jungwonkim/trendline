#include "Platform.h"
#include "Debug.h"
#include "PMU.h"
#include "Sampler.h"
#include "Timer.h"
#include "Type.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace yamp {

Platform::Platform() {
  init_ = false;
  finalize_ = false;

  ncpus_ = YAMP_MAX_EVENTS_SET;
  freq_ = 10;
  start_ = 0;
  csv_ = false;

  sid_ = 0;

  nsamplers_ = 0;
  for (int i = 0; i < YAMP_MAX_EVENTS_SET; i++) samplers_[i] = NULL;

  cmd_ = 1;

  pmu_ = new PMU();
  timer_ = new Timer();

  _debug("%d\n", ncpus_);
}

Platform::~Platform() {
  if (!init_) return;
  for (int i = 0; i < YAMP_MAX_EVENTS_SET; i++)
    if (samplers_[i] != NULL) delete samplers_[i];
  delete pmu_;
  delete timer_;
}

int Platform::Init(int* argc, char*** argv) {
  argc_ = argc;
  argv_ = argv;

  _info("cpus[%d] Freq[%d] Start[%d] output_csv[%d]", ncpus_, freq_, start_, csv_);
  return GetOptions();
}

int Platform::SetSID() {
  char filename[256];
  for (sid_ = 0; sid_ < 9999; sid_++) {
    sprintf(filename, YAMP_LOG_FILENAME, sid_);
    if (access(filename, F_OK) != 0) return YAMP_OK;
  }
  return YAMP_ERR;
}

int Platform::Run() {
  SetSID();

  for (int i = 0; i < ncpus_; i++) {
    samplers_[nsamplers_++] = new Sampler(i, pmu_->Events(i), freq_, start_);
  }

  if (strcmp("--", (*argv_)[cmd_]) == 0) cmd_++;

  pid_t pid = fork();
  if (pid == 0)
    if (execvp((*argv_)[cmd_], *argv_ + cmd_) == -1) {
      perror("execvp");
      _error("%s", (*argv_)[cmd_]);
      exit(EXIT_FAILURE);
    }

  for (int i = 0; i < nsamplers_; i++) {
    samplers_[i]->set_pid(pid);
    if (freq_ > 0) samplers_[i]->Start();
  }

  int status;
  waitpid(pid, &status, 0);

  for (int i = 0; i < nsamplers_; i++) {
    if (freq_ > 0) samplers_[i]->Stop();
    else samplers_[i]->Sample();
  }
  for (int i = 0; i < nsamplers_; i++)
    if (WEXITSTATUS(status) == EXIT_SUCCESS) samplers_[i]->Print();
  return YAMP_OK;
}

int Platform::GetOptions() {
  int opt;
  while ((opt = getopt(*argc_, *argv_, "C:e:F:s:o")) != -1) {
    switch (opt) {
      case 'C':
        ncpus_ = atoi(optarg);
        if (ncpus_ < 1) ncpus_ = 1;
        cmd_ += 2;
        break;
      case 'e': {
        char* s = NULL;
        char* rest = optarg;
        if (strchr(optarg, '-')) {
          int cpu0 = atoi(strtok_r(rest, "-", &rest));
          int cpu1 = atoi(strtok_r(rest, "-", &rest));
          _debug("cpu [%d-%d]", cpu0, cpu1);
        } else {
          while ((s = strtok_r(rest, ",", &rest))) {
            int event = atoi(s);
            _debug("event[%d]", event);
          }
        }
        cmd_ += 2;
        break;
      }
      case 'F':
        freq_ = atoi(optarg);
        if (freq_ < 0) freq_ = 1;
        cmd_ += 2;
        break;
      case 's':
        start_ = atoi(optarg);
        if (start_ < 0) freq_ = 0;
        cmd_ += 2;
        break;
      case 'o':
        csv_ = true;
        cmd_ += 1;
        break;
      default:
        return YAMP_ERR;
    }
  }
  return YAMP_OK;
}

double Platform::Now() {
  return timer_->Now();
}

Platform* Platform::singleton_ = NULL;

Platform* Platform::GetPlatform() {
  if (singleton_ == NULL) singleton_ = new Platform();
  return singleton_;
}

int Platform::Finalize() {
  return YAMP_OK;
}

} /* namespace yamp */
