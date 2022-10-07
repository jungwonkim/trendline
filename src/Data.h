#ifndef YAMP_SRC_DATA_H
#define YAMP_SRC_DATA_H

#include "Type.h"

#define YAMP_DATA_NCHUNKS     1024

typedef struct _yamp_row {
  double time;
  u_int64_t data[YAMP_MAX_EVENTS];
} yamp_row;

namespace yamp {

class Data {
public:
  Data();
  ~Data();

  int NewEpoch(double time);
  int AddCount(int idx, u_int64_t data);
  int Commit();

  int nrows() { return row_; }
  yamp_row* current() { return current_; }

private:
  int row_;
  yamp_row* chunk0_;
  yamp_row* chunk1_;
  yamp_row* current_;
};

} /* namespace yamp */

#endif /* YAMP_SRC_DATA_H */
