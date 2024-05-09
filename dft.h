#ifndef DFT_H_
#define DFT_H_

#include <complex.h>
#include <stdint.h>

#define BUFFER 2048

double _Complex *dft(const double _Complex *, const uint32_t);

#endif // !
