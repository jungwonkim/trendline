#include "CommandHelp.h"
#include "Debug.h"
#include "Platform.h"

namespace trendline {

CommandHelp::CommandHelp(int argc, char** argv) : Command(argc, argv) {
  fp_ = stdout;
}

CommandHelp::~CommandHelp() {
}

int CommandHelp::Init() {
  return TRENDLINE_OK;
}

int CommandHelp::Run() {
  fprintf(fp_, "\n usage: %s [stat | record | list | aggregate] [-C CPU] [-F FREQ] [-G GROUP] [-o] -- PROGRAM [ARGS]\n\n", argv_[0]);
  return TRENDLINE_OK;
}

} /* namespace trendline */
