#ifndef TRENDLINE_SRC_PRINTER_H
#define TRENDLINE_SRC_PRINTER_H

#include <stdio.h>

namespace trendline {

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

} /* namespace trendline */

#endif /* TRENDLINE_SRC_PRINTER_H */
