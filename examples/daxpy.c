#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int SIZE = argc > 1 ? atoi(argv[1]) : 1024;

  double *z = (double*) malloc(3 * SIZE * sizeof(double));
  double *x = z + SIZE;
  double *y = x + SIZE;
  double a = 3.14;

  for (int i = 0; i < SIZE; i++) {
    z[i] = a * x[i] + y[i];
  }

  return 0;
}
