#include "Platform.h"
#include "Command.h"
#include "Debug.h"
#include "Timer.h"
#include "Type.h"
#include "PMU.h"
#include <stdlib.h>
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
  argc_ = *argc;
  argv_ = *argv;

  if (argc_ < 2) {
    _error("argc[%d]", argc_);
    return YAMP_ERR;
  }

  cmd_ = Command::CreateCommand(argv_[1]);
  if (!cmd_) return YAMP_ERR;
  if (cmd_) cmd_->Init(argc, argv);
  return YAMP_OK;
}

int Platform::Run() {
  return cmd_ ? cmd_->Run() : YAMP_ERR;
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
