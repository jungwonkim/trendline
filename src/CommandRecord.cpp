#include "CommandRecord.h"
#include "Debug.h"
#include "Type.h"
#include "PMU.h"
#include "Sampler.h"
#include "Timer.h"
#include "Platform.h"
#include "Printer.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace yamp {

CommandRecord::CommandRecord() {
  ncpus_ = YAMP_MAX_EVENTS_SET;
  freq_ = 10;
  start_ = 0;
  csv_ = false;

  nsamplers_ = 0;
  for (int i = 0; i < YAMP_MAX_EVENTS_SET; i++) samplers_[i] = NULL;
  printer_ = NULL;
  fp_ = stderr;

  pmu_ = Platform::GetPlatform()->pmu();
}

CommandRecord::~CommandRecord() {
  if (printer_) delete printer_;
  if (fp_ != stderr) fclose(fp_);
}

int CommandRecord::Init(int* argc, char*** argv) {
  argc_ = *argc;
  argv_ = *argv;

  GetOptions();
  InitPrinterOutput();
  printer_ = new Printer(fp_);
  return YAMP_OK;
}

int CommandRecord::InitPrinterOutput() {
  if (!csv_) return YAMP_OK;
  char filename[256];
  for (int i = 0; i < 9999; i++) {
    sprintf(filename, YAMP_LOG_FILENAME, i);
    if (access(filename, F_OK) != 0) {
      fp_ = fopen(filename, "a");
      return fp_ ? YAMP_OK : YAMP_ERR;
    }
  }
  return YAMP_ERR;
}

int CommandRecord::Run() {
  for (int i = 0; i < ncpus_; i++) {
    samplers_[nsamplers_++] = new Sampler(i, pmu_->Events(i), freq_, start_);
  }

  pid_t pid = fork();
  int prog = optind + 1;
  if (pid == 0)
    if (execvp(argv_[prog], argv_ + prog) == -1) {
      perror("execvp");
      _error("program[%d][%s]", prog, argv_[prog]);
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
    if (WEXITSTATUS(status) == EXIT_SUCCESS) printer_->Print(samplers_[i]);
  return YAMP_OK;
}

int CommandRecord::GetOptions() {
  int opt;
  while ((opt = getopt(argc_, argv_, "C:e:F:s:o")) != -1) {
    switch (opt) {
      case 'C':
        ncpus_ = atoi(optarg);
        if (ncpus_ < 1) ncpus_ = 1;
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
        break;
      }
      case 'F':
        freq_ = atoi(optarg);
        if (freq_ < 0) freq_ = 1;
        break;
      case 's':
        start_ = atoi(optarg);
        if (start_ < 0) freq_ = 0;
        break;
      case 'o':
        csv_ = true;
        break;
      default:
        return YAMP_ERR;
    }
  }
  return YAMP_OK;
}


} /* namespace yamp */
