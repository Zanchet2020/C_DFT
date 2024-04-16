#include "dft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  uint32_t N = 2024;

  double complex *input = malloc(N * sizeof(double complex));
  double complex *output = NULL;

  for (uint32_t i = 0; i < N; ++i) {
    input[i] = CMPLX(cos())
  }

  output = dft(input, N);

  return 0;
}
