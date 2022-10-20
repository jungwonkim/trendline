#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int SIZE = argc > 1 ? atoi(argv[1]) : 1024;

  float (*a)[SIZE] = (float(*)[SIZE]) malloc(2 * SIZE * SIZE * sizeof(float));
  float (*b)[SIZE] = a + SIZE;
  float *c = (float*) malloc(SIZE * sizeof(float));

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      b[i][j] = a[i][j] * c[j];

  return 0;
}

