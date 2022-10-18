#ifndef TRENDLINE_SRC_COMMAND_CORREL_H
#define TRENDLINE_SRC_COMMAND_CORREL_H

#include "Command.h"
#include "Type.h"

namespace trendline {

class Data;

class CommandCorrel : public Command {
public:
  CommandCorrel(int argc, char** argv);
  virtual ~CommandCorrel();

  virtual int Init();
  virtual int Run();

private:
  int InitOptions();
  int InitPrinterOutput();

  int CalculatePearsons();
  double CalculatePearson(int x, int y, int64_t* diff, u_int64_t* diff_sq, u_int64_t* diff_sq_sum);

private:
  char* inputfile_;
  bool csv_;
  int skip0_;
  int skip1_;
  int scale_;

  Data* data_;
  FILE* fp_;

  u_int64_t avg_[TRENDLINE_MAX_COUNTERS];
  char events_[TRENDLINE_MAX_COUNTERS][128];
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_CORREL_H */

