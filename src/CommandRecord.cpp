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

namespace trendline {

CommandRecord::CommandRecord(int argc, char** argv) : Command(argc, argv) {
  freq_ = 10;
  csv_ = false;

  max_nsamplers_ = nsamplers_ = Platform::GetPlatform()->pmu()->ngroups();
  samplers_ = new Sampler*[nsamplers_];
  printer_ = new Printer();
  fp_ = stderr;

  pmu_ = Platform::GetPlatform()->pmu();
}

CommandRecord::~CommandRecord() {
  if (printer_) delete printer_;
  if (fp_ != stderr) fclose(fp_);
  for (int i = 0; i < nsamplers_; i++) delete samplers_[i];
  delete[] samplers_;
}

int CommandRecord::Init() {
  InitOptions();
  return TRENDLINE_OK;
}

int CommandRecord::InitPrinterOutput() {
  if (!csv_) return TRENDLINE_OK;
  char filename[256];
  for (int i = 0; i < 9999; i++) {
    sprintf(filename, TRENDLINE_LOG_FILENAME, i);
    if (access(filename, F_OK) != 0) {
      fp_ = fopen(filename, "a");
      return fp_ ? TRENDLINE_OK : TRENDLINE_ERR;
    }
  }
  return TRENDLINE_ERR;
}

int CommandRecord::Run() {
  for (int i = 0; i < nsamplers_; i++) samplers_[i] = new Sampler(i, pmu_->Events(i), freq_);

  pid_t pid = fork();
  int prog = optind + 1;
  if (pid == 0)
    if (execvp(argv_[prog], argv_ + prog) == -1) {
      perror("execvp");
      _error("program[%d][%s]", prog, argv_[prog]);
      exit(EXIT_FAILURE);
    }

  for (int i = 0; i < nsamplers_; i++) samplers_[i]->Start();

  int status;
  waitpid(pid, &status, 0);

  for (int i = 0; i < nsamplers_; i++) samplers_[i]->Stop(false);
  for (int i = 0; i < nsamplers_; i++) samplers_[i]->Join();

  InitPrinterOutput();
  for (int i = 0; i < nsamplers_; i++)
    if (WEXITSTATUS(status) == EXIT_SUCCESS) printer_->Print(fp_, samplers_[i]);
  return TRENDLINE_OK;
}

int CommandRecord::InitOptions() {
  int opt;
  while ((opt = getopt(argc_, argv_, "C:e:F:o")) != -1) {
    switch (opt) {
      case 'C':
        nsamplers_ = atoi(optarg);
        if (nsamplers_ < 1) nsamplers_ = 1;
        else if (nsamplers_ > max_nsamplers_) nsamplers_ = max_nsamplers_;
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
        if (freq_ <= 0) freq_ = 1;
        break;
      case 'o':
        csv_ = true;
        break;
      default:
        return TRENDLINE_ERR;
    }
  }
  return TRENDLINE_OK;
}

} /* namespace trendline */
