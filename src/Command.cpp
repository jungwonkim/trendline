#include "Command.h"
#include "CommandAggregate.h"
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
  if (strcmp("stats", cmd) == 0) return NULL;
  if (strcmp("record", cmd) == 0) return new CommandRecord(argc, argv);
  if (strcmp("aggregate", cmd) == 0) return new CommandAggregate(argc, argv);
  
  return NULL;
}

} /* namespace trendline */
