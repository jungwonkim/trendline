#include "PMUNeoverseV1.h"
#include "Type.h"
#include "Debug.h"

#define NCOUNTERS           6

#define L1I_CACHE_REFILL    0x01
#define L1I_TLB_REFILL      0x02
#define L1D_CACHE_REFILL    0x03
#define L1D_CACHE           0x04
#define L1D_TLB_REFILL      0x05
#define INST_RETIRED        0x08
#define BR_MIS_PRED         0x10
#define CPU_CYCLES          0x11
#define BR_PRED             0x12
#define MEM_ACCESS          0x13
#define LI1_CACHE           0x14
#define L2D_CACHE           0x16
#define L2D_CACHE_REFILL    0x17
#define BUS_ACCESS          0x19
#define INST_SPEC           0x1b
#define BR_RETIRED          0x21
#define BR_MIS_PRED_RETIRED 0x22
#define L1D_TLB             0x25
#define L1I_TLB             0x26
#define L2D_TLB_REFILL      0x2d
#define L2D_TLB             0x2f
#define LL_CACHE_RD         0x36
#define LL_CACHE_MISS_RD    0x37
#define OP_RETIRED          0x3a
#define OP_SPEC             0x3b
#define STALL               0x3c
#define STALL_SLOT_BACKEND  0x3d
#define STALL_SLOT_FRONTEND 0x3e
#define STALL_SLOT          0x3f
#define LD_SPEC             0x70
#define ST_SPEC             0x71
#define LDST_SPEC           0x72
#define DP_SPEC             0x73
#define ASE_SPEC            0x74
#define VFP_SPEC            0x75

namespace trendline {

PMUNeoverseV1::PMUNeoverseV1() : PMU() {
  ncounters_ = NCOUNTERS;
  ngroups_ = 7;
  events_ = new int[ngroups_ * NCOUNTERS] {
    CPU_CYCLES, INST_RETIRED, OP_SPEC, OP_RETIRED, STALL_SLOT_FRONTEND, STALL_SLOT_BACKEND,
    DP_SPEC, ASE_SPEC, VFP_SPEC, BR_PRED, LD_SPEC, ST_SPEC,
    STALL_SLOT_FRONTEND, OP_SPEC, OP_RETIRED, BR_PRED, BR_MIS_PRED, -1,
    STALL_SLOT_BACKEND, L1D_CACHE, L1D_CACHE_REFILL, L1D_TLB, L1D_TLB_REFILL, -1,
    STALL_SLOT_BACKEND, L2D_CACHE, L2D_CACHE_REFILL, L2D_TLB, L2D_TLB_REFILL, -1,
    STALL_SLOT_BACKEND, LL_CACHE_RD, LL_CACHE_MISS_RD, MEM_ACCESS, BUS_ACCESS, -1,
    STALL_SLOT_BACKEND, L1D_CACHE, L1D_CACHE_REFILL, L2D_CACHE, L2D_CACHE_REFILL, LL_CACHE_RD,
  };
}

PMUNeoverseV1::~PMUNeoverseV1() {
}

int PMUNeoverseV1::InitS2E() {
  S2E(L1I_CACHE_REFILL);
  S2E(L1I_TLB_REFILL);
  S2E(L1D_CACHE_REFILL);
  S2E(L1D_CACHE);
  S2E(L1D_TLB_REFILL);
  S2E(INST_RETIRED);
  S2E(BR_MIS_PRED);
  S2E(CPU_CYCLES);
  S2E(BR_PRED);
  S2E(MEM_ACCESS);
  S2E(LI1_CACHE);
  S2E(L2D_CACHE);
  S2E(L2D_CACHE_REFILL);
  S2E(BUS_ACCESS);
  S2E(INST_SPEC);
  S2E(BR_RETIRED);
  S2E(BR_MIS_PRED_RETIRED);
  S2E(L1D_TLB);
  S2E(L1I_TLB);
  S2E(L2D_TLB_REFILL);
  S2E(L2D_TLB);
  S2E(LL_CACHE_RD);
  S2E(LL_CACHE_MISS_RD);
  S2E(OP_RETIRED);
  S2E(OP_SPEC);
  S2E(STALL);
  S2E(STALL_SLOT_BACKEND);
  S2E(STALL_SLOT_FRONTEND);
  S2E(STALL_SLOT);
  S2E(LD_SPEC);
  S2E(ST_SPEC);
  S2E(LDST_SPEC);
  S2E(DP_SPEC);
  S2E(ASE_SPEC);
  S2E(VFP_SPEC);
  return TRENDLINE_OK;
}

int* PMUNeoverseV1::Events(int i) {
  return ((int(*)[NCOUNTERS]) (events_))[i];
}

} /* namespace trendline */
