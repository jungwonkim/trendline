#include <stdio.h>
#include "Sampler.h"

int main(int argc, char** argv) {
  yamp::Sampler* sampler = new yamp::Sampler();
  sampler->Run(argv);
  sampler->Print();
  delete sampler;
  return 0;
}

