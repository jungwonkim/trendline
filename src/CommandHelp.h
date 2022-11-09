#ifndef TRENDLINE_SRC_COMMAND_HELP_H
#define TRENDLINE_SRC_COMMAND_HELP_H

#include "Command.h"

namespace trendline {

class PMU;

class CommandHelp: public Command {
public:
  CommandHelp(int argc, char** argv);
  virtual ~CommandHelp();

  virtual int Init();
  virtual int Run();

private:
  FILE* fp_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_HELP_H */
