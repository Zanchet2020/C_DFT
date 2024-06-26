#include "dft.h"
#include <complex.h>
#include <math.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  uint32_t N = 2024;
  uint32_t lines = 0, columns = 0;

  initscr();
  nodelay(stdscr, TRUE);
  start_color();
  curs_set(FALSE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  box(stdscr, 0, 0);
  getmaxyx(stdscr, lines, columns);
  double complex *input = malloc(N * sizeof(double complex));
  double complex *output = malloc(N * sizeof(double complex));


  
  for (uint32_t i = 0; i < N; ++i) {
    input[i] = CMPLX(cos(3 * 2 * M_PI * i / (double)N), 0);
  }

  dft(output, input, N);
  int span = 2024 / 120;
  for (uint32_t i = 0; i < 120; ++i) {
    double avg = 0;
    for(int j = 0; j < span; j++){
      avg += cabs(output[i*span+j]);
    }
    avg = avg / span;
    for (uint32_t j = 1; j < lines - 1; j++) {
        if (j >= lines - 500 * avg && j < lines - 1){
	  //int a = L'\u2588';
          mvaddch(j, i, 'X');
	}
        else
          mvaddch(j, i, ' ');
      }
    /* printf("Real: %.2f      Img: %.2f       Mod: %.2f\n", creal(avg), */
    /*        cimag(avg), cabs(avg)); */
  }

  //  for (uint32_t i = 0; i < N; ++i) {
  //    if (i % 10 == 0)
  //      printf("input %d: %.2f\n", i, creal(input[i]));
  //  }

  free(output);
  free(input);

  return 0;
}
