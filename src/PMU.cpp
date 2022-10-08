#include "PMU.h"

namespace yamp {

PMU::PMU() {

}

PMU::~PMU() {

}

const char* PMU::String(int event) {
  switch (event) {
    case 0x11: return "CPU_CYCLES";
    case 0x3a: return "OP_RETIRED";
    case 0x3b: return "OP_SPEC";
    case 0x3c: return "STALL";
    case 0x3d: return "STALL_SLOT_BACKEND";
    case 0x3e: return "STALL_SLOT_FRONTEND";
    case 0x3f: return "STALL_SLOT";
               return "UNKNOWN";
  }
}

} /* namespace yamp */
