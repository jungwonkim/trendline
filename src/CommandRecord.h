#ifndef TRENDLINE_SRC_COMMAND_RECORD_H
#define TRENDLINE_SRC_COMMAND_RECORD_H

#include "Command.h"

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
  int* GetEvents(int i);

protected:
  bool csv_;
  int freq_;
  int group_;
  int nsamplers_;
  int max_nsamplers_;

  Sampler** samplers_;
  Printer* printer_;
  FILE* fp_;
  PMU* pmu_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_RECORD_H */
