#include <stdio.h>
#include "Platform.h"

int usage(char* cmd) {
  printf("\n usage: %s [-e EVENTSET] [-F FREQ] [-o] -- PROGRAM [ARGS]\n\n", cmd);
  return 1;
}

int main(int argc, char** argv) {
  if (argc < 2) return usage(argv[0]);
  yamp::Platform* platform = yamp::Platform::GetPlatform();
  platform->Init(&argc, &argv);
  platform->Run();
  platform->Finalize();
  return 0;
}

