#include "CommandStat.h"
#include "Debug.h"
#include "Sampler.h"
#include "PMU.h"
#include "Printer.h"
#include <unistd.h>
#include <sys/wait.h>

namespace trendline {

CommandStat::CommandStat(int argc, char** argv) : CommandRecord(argc, argv) {
  freq_ = 0;
  csv_ = false;
}

CommandStat::~CommandStat() {
}

int CommandStat::Run() {
  for (int i = 0; i < nsamplers_; i++) samplers_[i] = new Sampler(i, GetEvents(i), freq_);

  pid_t pid = fork();
  int prog = optind + 1;
  if (pid == 0)
    if (execvp(argv_[prog], argv_ + prog) == -1) {
      perror("execvp");
      _error("program[%d][%s]", prog, argv_[prog]);
      exit(EXIT_FAILURE);
    }

  for (int i = 0; i < nsamplers_; i++) samplers_[i]->Reset();

  int status;
  waitpid(pid, &status, 0);

  for (int i = 0; i < nsamplers_; i++) samplers_[i]->Sample();
  for (int i = 0; i < nsamplers_; i++)
    if (WEXITSTATUS(status) == EXIT_SUCCESS) printer_->Print(fp_, samplers_[i]);
  return TRENDLINE_OK;
}

} /* namespace trendline */
