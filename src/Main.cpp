#include <stdio.h>
#include "Platform.h"
#include "Debug.h"

int main(int argc, char** argv) {
  trendline::Platform* platform = trendline::Platform::GetPlatform();
  if (platform->Init(&argc, &argv) == TRENDLINE_ERR) return 1;
  platform->Run();
  platform->Finalize();
  return 0;
}

