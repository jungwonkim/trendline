#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int SIZE = argc > 1 ? atoi(argv[1]) : 1024;

  double (*a)[SIZE] = (double(*)[SIZE]) malloc(2 * SIZE * SIZE * sizeof(double));
  double (*b)[SIZE] = a + SIZE;
  double *c = (double*) malloc(SIZE * sizeof(double));

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      b[i][j] = a[i][j] * c[j];

  return 0;
}

