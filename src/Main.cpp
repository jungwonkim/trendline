#include <stdio.h>
#include "Sampler.h"

int usage(char* cmd) {
  printf("\n usage: %s PROGRAM [ARGS]\n\n", cmd);
  return 1;
}

int main(int argc, char** argv) {
  if (argc < 2) return usage(argv[0]);
  yamp::Sampler* sampler = new yamp::Sampler();
  sampler->Run(argv);
  sampler->Print();
  delete sampler;
  return 0;
}

