#include "dft.h"
#include <complex.h>
#include <math.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  uint32_t N = 2024;

  double complex *input = malloc(N * sizeof(double complex));
  double complex *output = NULL;

  for (uint32_t i = 0; i < N; ++i) {
    input[i] = CMPLX(cos(2 * M_PI * i / (double)N), 0);
  }

  output = dft(input, N);

  for (uint32_t i = 0; i < 10; ++i) {
    printf("Real: %.2f      Img: %.2f       Mod: %.2f\n", creal(output[i]),
           cimag(output[i]), cabs(output[i]));
  }

  //  for (uint32_t i = 0; i < N; ++i) {
  //    if (i % 10 == 0)
  //      printf("input %d: %.2f\n", i, creal(input[i]));
  //  }

  free(output);
  free(input);

  return 0;
}
