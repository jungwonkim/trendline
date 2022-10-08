#include "Platform.h"
#include "Debug.h"
#include "PMU.h"
#include "Sampler.h"
#include "Timer.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace yamp {

Platform::Platform() {
  init_ = false;
  finalize_ = false;

  freq_ = 1;
  csv_ = false;

  cmd_ = 1;

  ncpus_ = 2;

  nsamplers_ = 0;
  for (int i = 0; i < YAMP_MAX_EVENTS_SET; i++) samplers_[i] = NULL;

  pmu_ = new PMU();
  timer_ = new Timer();
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

  return GetOptions();
}

int Platform::Run() {
  for (int i = 0; i < ncpus_; i++) {
    samplers_[nsamplers_++] = new Sampler(i, pmu_->Events(i), freq_);
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
    samplers_[i]->Start();
  }

  int status;
  waitpid(pid, &status, 0);

  for (int i = 0; i < nsamplers_; i++) samplers_[i]->Stop();
  for (int i = 0; i < nsamplers_; i++)
    if (WEXITSTATUS(status) == EXIT_SUCCESS) samplers_[i]->Print();
  return YAMP_OK;
}

int Platform::GetOptions() {
  int opt;
  while ((opt = getopt(*argc_, *argv_, "f:o")) != -1) {
    switch (opt) {
      case 'f':
        freq_ = atoi(optarg);
        _debug("freq[%d]", freq_);
        cmd_ += 2;
        break;
      case 'o':
        csv_ = true;
        _debug("csv[%d]", 1);
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
