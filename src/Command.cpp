#include "Command.h"
#include "CommandAggregate.h"
#include "CommandStat.h"
#include "CommandRecord.h"
#include "Debug.h"
#include <string.h>

namespace trendline {

Command::Command(int argc, char** argv) {
  argc_ = argc;
  argv_ = argv;
}

Command::~Command() {

}

Command* Command::CreateCommand(const char* cmd, int argc, char** argv) {
  if (strcmp("s", cmd) == 0 || strcmp("stat", cmd) == 0) 
    return new CommandStat(argc, argv);
  if (strcmp("r", cmd) == 0 || strcmp("record", cmd) == 0)
    return new CommandRecord(argc, argv);
  if (strcmp("dr", cmd) == 0 || strcmp("aggregate", cmd) == 0)
    return new CommandAggregate(argc, argv);
  _error("cmd[%s]", cmd);
  return NULL;
}

} /* namespace trendline */
