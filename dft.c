#include "dft.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

double complex *dft(const double complex *input, const uint32_t K) {
  const uint32_t N = K;
  double complex *output = malloc(K * sizeof(double complex));
  const double complex constant_value = (-I * 2.0 * M_PI) / N;
  for (uint32_t k = 0; k < K; ++k) {
    output[k] = 0;
    const double complex exponent = constant_value * k;
    for (uint32_t n = 0; n < N; ++n) {
      output[k] += input[n] * cexp(exponent * n);
    }
    output[k] = output[k] / (double)N;
  }
  return output;
}
