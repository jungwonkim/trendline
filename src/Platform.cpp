#include "Platform.h"
#include "Debug.h"
#include "PMU.h"
#include "Sampler.h"
#include "Type.h"
#include "Timer.h"
#include <unistd.h>
#include <sys/wait.h>

namespace yamp {

Platform::Platform() {
  init_ = false;
  finalize_ = false;

  pmu_ = new PMU();
  timer_ = new Timer();
}

Platform::~Platform() {
  if (!init_) return;
  delete pmu_;
  delete timer_;
}

int Platform::Init(int* argc, char*** argv) {
  argc_ = argc;
  argv_ = argv;
  return YAMP_OK;
}

int Platform::Run() {
  int events[5] = { 0x11, 0x3b, 0x3a, 0x3e, 0x3d };
  Sampler* sampler = new Sampler(-1, events, 5, 10);

  pid_t pid = fork();
  if (pid == 0)
    if (execvp((*argv_)[1], *argv_ + 1) == -1) _error("%s", (*argv_)[1]);

  sampler->set_pid(pid);
  sampler->Start();

  int status;
  waitpid(pid, &status, 0);

  sampler->Stop();
  sampler->Print();
  delete sampler;
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
