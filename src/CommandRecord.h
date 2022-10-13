#ifndef TRENDLINE_SRC_COMMAND_RECORD_H
#define TRENDLINE_SRC_COMMAND_RECORD_H

#include "Command.h"
#include "Type.h"
#include <stdio.h>

namespace trendline {

class Sampler;
class Printer;
class PMU;

class CommandRecord : public Command {
public:
  CommandRecord(int argc, char** argv);
  virtual ~CommandRecord();

  virtual int Init();
  virtual int Run();

protected:
  int InitPrinterOutput();
  int InitOptions();

protected:
  bool csv_;
  int freq_;
  int ncpus_;
  int nsamplers_;

  Sampler* samplers_[TRENDLINE_MAX_EVENTS_SET];
  Printer* printer_;
  FILE* fp_;
  PMU* pmu_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_RECORD_H */
