#include "Data.h"
#include "Debug.h"

namespace yamp {

Data::Data() {
  rid_ = 0;
  if (posix_memalign((void**) &rows_, 0x1000, YAMP_MAX_ROWS * sizeof(yamp_row)) != 0)
    _error("YAMP_MAX_ROWS[%llu]", YAMP_MAX_ROWS);
}

Data::~Data() {
  free(rows_);
}

int Data::AddTime(double time) {
  rows_[rid_].time = time;
  return YAMP_OK;
}

int Data::AddCount(int idx, u_int64_t data) {
  rows_[rid_].data[idx] = data;
  return YAMP_OK;
}

int Data::Commit() {
  if (rid_ >= YAMP_MAX_ROWS - 1) {
    _error("rid[%d]", rid_);
    return YAMP_ERR;
  }
  rid_++;
  return YAMP_OK;
}

} /* namespace yamp */
