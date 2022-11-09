#ifndef TRENDLINE_SRC_COMMAND_H
#define TRENDLINE_SRC_COMMAND_H

#include "Config.h"

namespace trendline {

class Command {
public:
  Command(int argc, char** argv);
  virtual ~Command();

  virtual int Init() = 0;
  virtual int Run() = 0;

public:
  static Command* CreateCommand(const char* cmd, int argc, char** argv);

protected:
  int argc_;
  char** argv_;

};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_COMMAND_H */
