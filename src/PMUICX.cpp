#include "PMUICX.h"
#include "Type.h"
#include "Debug.h"

// https://perfmon-events.intel.com/icelake.html

#define NCOUNTERS                     8

#define INST_RETIRED                  0xc0
#define CPU_CLK_UNHALTED              0x3c
#define UOPS_ISSUED_ANY               0x0e|(0x01<<8)
#define UOPS_RETIRED_SLOTS            0xc2|(0x02<<8)
#define TOPDOWN_SLOTS                 0xa4|(0x01<<8)
#define TOPDOWN_BACKEND_BOUND_SLOTS   0xa4|(0x02<<8)

namespace trendline {

PMUICX::PMUICX() {
  ncounters_ = NCOUNTERS;
  ngroups_ = 1;
  events_ = new int[ngroups_ * NCOUNTERS] {
    CPU_CLK_UNHALTED, INST_RETIRED, UOPS_ISSUED_ANY, UOPS_RETIRED_SLOTS, TOPDOWN_SLOTS, TOPDOWN_BACKEND_BOUND_SLOTS, -1, -1,
  };
  InitS2E();
  InitE2S();
}

PMUICX::~PMUICX() {

}

int PMUICX::InitS2E() {
  S2E(INST_RETIRED);
  S2E(CPU_CLK_UNHALTED);
  S2E(UOPS_ISSUED_ANY);
  S2E(UOPS_RETIRED_SLOTS);
  S2E(TOPDOWN_SLOTS);
  S2E(TOPDOWN_BACKEND_BOUND_SLOTS);
  return TRENDLINE_OK;
}

int* PMUICX::Events(int i) {
  return ((int(*)[NCOUNTERS]) (events_))[i];
}

} /* namespace trendline */
