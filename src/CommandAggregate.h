#ifndef TRENDLINE_SRC_COMMAND_AGGREGATE_H
#define TRENDLINE_SRC_COMMAND_AGGREGATE_H

#include "Command.h"
#include "Type.h"
#include <stdio.h>

namespace trendline {

class Data;

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
  FILE* fp_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_AGGREGATE_H */
