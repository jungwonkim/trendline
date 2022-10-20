#ifndef TRENDLINE_SRC_COMMAND_LIST_H
#define TRENDLINE_SRC_COMMAND_LIST_H

#include "Command.h"

namespace trendline {

class PMU;

class CommandList : public Command {
public:
  CommandList(int argc, char** argv);
  virtual ~CommandList();

  virtual int Init();
  virtual int Run();

private:
  FILE* fp_;
  PMU* pmu_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_LIST_H */
