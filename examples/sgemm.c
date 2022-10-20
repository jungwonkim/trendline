#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int SIZE = argc > 1 ? atoi(argv[1]) : 1024;

  float (*a)[SIZE] = (float(*)[SIZE]) malloc(3 * SIZE * SIZE * sizeof(float));
  float (*b)[SIZE] = a + SIZE;
  float (*c)[SIZE] = b + SIZE;

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      for (int k = 0; k < SIZE; k++)
        c[i][j] += a[i][k] * b[k][j];

  return 0;
}

