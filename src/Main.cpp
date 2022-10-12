#include <stdio.h>
#include "Platform.h"

int usage(char* cmd) {
  printf("\n usage: %s [stats | record | aggregate] [-e EVENTSET] [-F FREQ] [-o] -- PROGRAM [ARGS]\n\n", cmd);
  return 1;
}

int main(int argc, char** argv) {
  trendline::Platform* platform = trendline::Platform::GetPlatform();
  if (platform->Init(&argc, &argv) == TRENDLINE_ERR) return usage(argv[0]);
  platform->Run();
  platform->Finalize();
  return 0;
}

