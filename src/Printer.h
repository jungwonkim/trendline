#ifndef YAMP_SRC_PRINTER_H
#define YAMP_SRC_PRINTER_H

#include <stdio.h>

namespace yamp {

class Data;
class PMU;
class Sampler;

class Printer {
public:
  Printer(FILE* fp);
  ~Printer();

  int Print(Sampler* sampler);

private:
  FILE* fp_;
  PMU* pmu_;

};

} /* namespace yamp */

#endif /* YAMP_SRC_PRINTER_H */
