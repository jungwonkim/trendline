# trendline
Yet Another Microarchitecture Profiler

## Support CPUs
ARM Neoverse N1, ARM Neoverse V1, Intel Ice Lake Xeon

## Requirements
CMake (>=2.8)
 
## Installation

You can download the trendline source code from GitHub:

    $ git clone https://github.com/jungwonkim/trendline.git
    $ cd trendline

You can build trendline with CMake and Make:

    $ mkdir build
    $ cd build
    $ cmake .. -DCMAKE_INSTALL_PREFIX=<install_dir>
    $ make install

### Running a test application

    $ tl record -C 0 -- taskset -c 0 build/apps/dgemm
    TIME(CPU0),CPU_CYCLES,INST_RETIRED,OP_SPEC,OP_RETIRED,STALL_SLOT_FRONTEND,STALL_SLOT_BACKEND
    0.11986,234096918,812320779,794471220,792470702,167875808,910428316
    0.22051,259243641,907786476,887115182,885610184,184538927,1002295019
    ..
    4.85021,258955147,913990001,893157552,891661817,185804311,992679241
    $
