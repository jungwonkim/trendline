#include <stdio.h>
#include "Platform.h"

int usage(char* cmd) {
  printf("\n usage: %s [stats | record | list | aggregate] [-C CPU] [-F FREQ] [-G GROUP] [-o] -- PROGRAM [ARGS]\n\n", cmd);
  return 1;
}

int main(int argc, char** argv) {
  trendline::Platform* platform = trendline::Platform::GetPlatform();
  if (platform->Init(&argc, &argv) == TRENDLINE_ERR) return usage(argv[0]);
  platform->Run();
  platform->Finalize();
  return 0;
}

