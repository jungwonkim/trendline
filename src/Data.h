#ifndef YAMP_SRC_DATA_H
#define YAMP_SRC_DATA_H

#include "Type.h"

#define YAMP_MAX_ROWS 1024 * 1024

typedef struct _yamp_row {
  double time;
  u_int64_t data[YAMP_MAX_EVENTS];
} yamp_row;

namespace yamp {

class Data {
public:
  Data();
  ~Data();

  int AddTime(double time);
  int AddCount(int idx, u_int64_t data);
  int Commit();

  int nrows() { return rid_; }
  yamp_row* rows() { return rows_; }

private:
  int rid_;
  yamp_row* rows_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_DATA_H */
