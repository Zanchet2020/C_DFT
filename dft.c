#include "dft.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

double complex *dft(const double complex *input, const uint32_t K) {
  const uint32_t N = K;
  double complex *output = malloc(K * sizeof(double complex));
  const double constant_value = 2 * M_PI * (1 / (double)N);
  for (uint32_t k = 0; k < K; ++k) {
    const double exponent = constant_value * k;
    for (uint32_t n = 0; n < K; ++n) {
      output[k] = input[n] * cexp(-I * exponent * n);
    }
  }
  return output;
}
