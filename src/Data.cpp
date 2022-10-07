#include "Data.h"
#include "Debug.h"

namespace yamp {

Data::Data() {
  chunk0_ = new yamp_row[YAMP_DATA_NCHUNKS];
  chunk1_ = new yamp_row[YAMP_DATA_NCHUNKS];
  current_ = chunk0_;
  row_ = 0;
}

Data::~Data() {
  delete[] chunk0_;
  delete[]  chunk1_;
}

int Data::NewEpoch(double time) {
  current_[row_].time = time;
  return YAMP_OK;
}

int Data::AddCount(int idx, u_int64_t data) {
  current_[row_].data[idx] = data;
  return YAMP_OK;
}

int Data::Commit() {
  if (row_++ >= YAMP_DATA_NCHUNKS) {
    if (current_= chunk0_) current_ = chunk1_;
    else current_ = chunk0_;
    row_ = 0;
  }
  return YAMP_OK;
}

} /* namespace yamp */
