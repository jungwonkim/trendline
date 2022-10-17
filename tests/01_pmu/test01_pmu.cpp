#include <stdio.h>
#include <PMUNeoverseV1.h>

using namespace trendline;

int main(int argc, char** argv) {
  PMUNeoverseV1* pmu = new PMUNeoverseV1();
  printf("string %s\n", pmu->String(0x11));
  printf("event  0x%x\n", pmu->Event("CPU_CYCLES"));

  printf("string %s\n", pmu->String(0xdeadcafe));
  printf("event  0x%x\n", pmu->Event("DEAD_CAFE"));
  return 0;
}
