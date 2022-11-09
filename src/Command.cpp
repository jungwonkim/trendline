#include "Command.h"
#include "CommandAggregate.h"
#include "CommandCorrel.h"
#include "CommandHelp.h"
#include "CommandList.h"
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
  if (cmd == NULL) return new CommandHelp(argc, argv);
  if (strcmp("stat", cmd) == 0) return new CommandStat(argc, argv);
  if (strcmp("record", cmd) == 0) return new CommandRecord(argc, argv);
  if (strcmp("list", cmd) == 0) return new CommandList(argc, argv);
  if (strcmp("correl", cmd) == 0) return new CommandCorrel(argc, argv);
  if (strcmp("dr", cmd) == 0 || strcmp("aggregate", cmd) == 0) return new CommandAggregate(argc, argv);
  return new CommandHelp(argc, argv);
}

} /* namespace trendline */
