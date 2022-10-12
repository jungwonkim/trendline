#include "Data.h"
#include "Debug.h"

namespace trendline {

Data::Data() {
  rid_ = 0;
  if (posix_memalign((void**) &rows_, 0x1000, TRENDLINE_MAX_ROWS * sizeof(trendline_row)) != 0)
    _error("TRENDLINE_MAX_ROWS[%llu]", TRENDLINE_MAX_ROWS);
}

Data::~Data() {
  free(rows_);
}

int Data::AddTime(double time) {
  rows_[rid_].time = time;
  return TRENDLINE_OK;
}

int Data::AddCount(int idx, u_int64_t data) {
  rows_[rid_].data[idx] = data;
  return TRENDLINE_OK;
}

int Data::Commit() {
  if (rid_ >= TRENDLINE_MAX_ROWS - 1) {
    _error("rid[%d]", rid_);
    return TRENDLINE_ERR;
  }
  rid_++;
  return TRENDLINE_OK;
}

int Data::ClearRow(trendline_row* row) {
  memset(row, 0, sizeof(trendline_row));
  return TRENDLINE_OK;
}

} /* namespace trendline */
