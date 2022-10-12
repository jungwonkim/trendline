#ifndef TRENDLINE_SRC_COMMAND_AGGREGATE_H
#define TRENDLINE_SRC_COMMAND_AGGREGATE_H

#include "Command.h"
#include "Type.h"
#include <stdio.h>

namespace trendline {

class Data;
class Sampler;
class Printer;
class PMU;

class CommandAggregate : public Command {
public:
  CommandAggregate(int argc, char** argv);
  virtual ~CommandAggregate();

  virtual int Init();
  virtual int Run();

private:
  int InitPrinterOutput();
  int InitOptions();

private:
  int aggr_;
  bool csv_;
  int skip0_;
  int skip1_;

  Data* data_;
  Sampler* samplers_[TRENDLINE_MAX_EVENTS_SET];
  Printer* printer_;
  FILE* fp_;
  PMU* pmu_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_AGGREGATE_H */
