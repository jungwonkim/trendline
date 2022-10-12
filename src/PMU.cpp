#include "PMU.h"

namespace trendline {

PMU::PMU() {
  events_ = (int(*)[TRENDLINE_MAX_EVENTS]) new int[TRENDLINE_MAX_EVENTS_SET * TRENDLINE_MAX_EVENTS] {
    0x11, 0x3b, 0x3a, 0x3e, 0x3d, -1,
    0x73, 0x74, 0x75, 0x12, 0x70, 0x71,
    0x3e, 0x3d, 0x1b, 0x13, 0x70, 0x71,
    0x3e, 0x01, 0x02, 0x14, 0x01, -1,
    0x3d, 0x03, 0x17, 0x37, 0x19, -1,
    0x3e, 0x26, 0x02, 0x14, 0x01, -1,
    0x3d, 0x25, 0x05, 0x04, 0x03, -1,
    0x3d, 0x2f, 0x2d, 0x16, 0x17, -1,
    0x3d, 0x36, 0x37, 0x13, 0x19, -1
  };
}

PMU::~PMU() {
  delete[] events_;
}

const char* PMU::String(int event) {
  switch (event) {
    case 0x01: return "L1I_CACHE_REFILL";
    case 0x02: return "L1I_TLB_REFILL";
    case 0x03: return "L1D_CACHE_REFILL";
    case 0x04: return "L1D_CACHE";
    case 0x05: return "L1D_TLB_CACHE";
    case 0x08: return "INST_RETIRED";
    case 0x11: return "CPU_CYCLES";
    case 0x12: return "BR_PRED";
    case 0x13: return "MEM_ACCESS";
    case 0x14: return "LI1_CACHE";
    case 0x16: return "L2D_CACHE";
    case 0x17: return "L2D_CACHE_REFILL";
    case 0x19: return "BUS_ACCESS";
    case 0x1b: return "INST_SPEC";
    case 0x25: return "L1D_TLB";
    case 0x26: return "L1I_TLB";
    case 0x2d: return "L2D_TLB_REFILL";
    case 0x2f: return "L2D_TLB";
    case 0x36: return "LL_CACHE_RD";
    case 0x37: return "LL_CACHE_MISS_RD";
    case 0x3a: return "OP_RETIRED";
    case 0x3b: return "OP_SPEC";
    case 0x3c: return "STALL";
    case 0x3d: return "STALL_SLOT_BACKEND";
    case 0x3e: return "STALL_SLOT_FRONTEND";
    case 0x3f: return "STALL_SLOT";
    case 0x70: return "LD_SPEC";
    case 0x71: return "ST_SPEC";
    case 0x72: return "LDST_SPEC";
    case 0x73: return "DP_SPEC";
    case 0x74: return "ASE_SPEC";
    case 0x75: return "VFP_SPEC";
               return "UNKNOWN";
  }
  return NULL;
}

} /* namespace trendline */
