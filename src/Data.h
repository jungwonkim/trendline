#ifndef TRENDLINE_SRC_DATA_H
#define TRENDLINE_SRC_DATA_H

#include "Config.h"

typedef struct _trendline_row {
  double time;
  u_int64_t data[TRENDLINE_MAX_COUNTERS];
} trendline_row;

namespace trendline {

class Data {
public:
  Data();
  ~Data();

  int AddTime(double time);
  int AddCount(int idx, u_int64_t data);
  int Commit();
  int Reset();
  int DeleteTail(int n);

  void set_nevents(int n) { nevents_ = n; }
  int nrows() { return rid_; }
  int nevents() { return nevents_; }
  trendline_row* rows() { return rows_; }

public:
  static int ClearRow(trendline_row* row);

private:
  int rid_;
  int nevents_;
  trendline_row* rows_;
};

} /* namespace trendline */

#endif /* TRENDLINE_SRC_DATA_H */
