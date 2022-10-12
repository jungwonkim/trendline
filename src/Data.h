#ifndef TRENDLINE_SRC_DATA_H
#define TRENDLINE_SRC_DATA_H

#include "Type.h"

#define TRENDLINE_MAX_ROWS 1024 * 1024

typedef struct _trendline_row {
  double time;
  u_int64_t data[TRENDLINE_MAX_EVENTS];
} trendline_row;

namespace trendline {

class Data {
public:
  Data();
  ~Data();

  int AddTime(double time);
  int AddCount(int idx, u_int64_t data);
  int Commit();

  int nrows() { return rid_; }
  trendline_row* rows() { return rows_; }

public:
  static int ClearRow(trendline_row* row);

private:
  int rid_;
  trendline_row* rows_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_DATA_H */
