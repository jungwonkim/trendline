#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <trendline/trendline.h>

int main(int argc, char** argv) {
  int SIZE = argc > 1 ? atoi(argv[1]) : 1024;

  double (*a)[SIZE] = (double(*)[SIZE]) malloc(SIZE * SIZE * sizeof(double));
  double (*b)[SIZE] = (double(*)[SIZE]) malloc(SIZE * SIZE * sizeof(double));
  double (*c)[SIZE] = (double(*)[SIZE]) malloc(SIZE * SIZE * sizeof(double));

  trendline_init(&argc, &argv);

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++) {
      a[i][j] = (double) i;
      b[i][j] = (double) j;
      c[i][j] = 0.0;
    }

  trendline_start();

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      for (int k = 0; k < SIZE; k++)
        c[i][j] += a[i][k] * b[k][j];

  trendline_stop();

  double sum = c[0][0] + c[SIZE - 1][SIZE - 1];

  printf("malloc_once[%d] SIZE[%d] SUM[%lf]\n", argc > 2, SIZE, sum);

  trendline_finalize();

  return 0;
}

