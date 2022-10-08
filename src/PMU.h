#ifndef YAMP_SRC_PMU_H
#define YAMP_SRC_PMU_H

namespace yamp {

class PMU {
public:
  PMU();
  ~PMU();

  const char* String(int event);
};

} /* namespace yamp */

#endif /* YAMP_SRC_PMU_H */
