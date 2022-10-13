#ifndef TRENDLINE_SRC_COMMAND_STAT_H
#define TRENDLINE_SRC_COMMAND_STAT_H

#include "CommandRecord.h"

namespace trendline {

class CommandStat : public CommandRecord {

public:
  CommandStat(int argc, char** argv);
  virtual ~CommandStat();

  virtual int Run();

};

} /* namespace trendline */


#endif /* TRENDLINE_SRC_COMMAND_STAT_H */

