#include "Command.h"
#include "CommandRecord.h"
#include "Debug.h"
#include <string.h>

namespace yamp {

Command::Command() {
}

Command::~Command() {

}

Command* Command::CreateCommand(const char* cmd) {
  if (strcmp("stats", cmd) == 0) return NULL;
  if (strcmp("record", cmd) == 0) return new CommandRecord();
  if (strcmp("aggregate", cmd) == 0) return NULL;
  
  return NULL;
}

} /* namespace yamp */
