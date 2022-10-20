#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int SIZE = argc > 1 ? atoi(argv[1]) : 1024;

  double (*a)[SIZE] = (double(*)[SIZE]) malloc(3 * SIZE * SIZE * sizeof(double));
  double (*b)[SIZE] = a + SIZE;
  double (*c)[SIZE] = b + SIZE;

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      for (int k = 0; k < SIZE; k++)
        c[i][j] += a[i][k] * b[k][j];

  return 0;
}

