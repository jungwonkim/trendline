#ifndef YAMP_SRC_PRINTER_H
#define YAMP_SRC_PRINTER_H

namespace yamp {

class Data;
class PMU;
class Sampler;

class Printer {
public:
  Printer(Sampler* sampler);
  ~Printer();

  int Print(Data* data);

private:
  Sampler* sampler_;
  PMU* pmu_;
  int nevents_;

};

} /* namespace yamp */

#endif /* YAMP_SRC_PRINTER_H */
