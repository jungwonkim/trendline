#ifndef YAMP_SRC_COMMAND_RECORD_H
#define YAMP_SRC_COMMAND_RECORD_H

#include "Command.h"
#include "Type.h"
#include <stdio.h>

namespace yamp {

class Sampler;
class Printer;
class PMU;

class CommandRecord : public Command {
public:
  CommandRecord();
  virtual ~CommandRecord();

  virtual int Init(int* argc, char*** argv);
  virtual int Run();

private:
  int InitPrinterOutput();
  int GetOptions();

private:
  bool csv_;
  int freq_;
  int start_;
  int ncpus_;
  int nsamplers_;

  int argc_;
  char** argv_;

  Sampler* samplers_[YAMP_MAX_EVENTS_SET];
  Printer* printer_;
  FILE* fp_;
  PMU* pmu_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_COMMAND_RECORD_H */
