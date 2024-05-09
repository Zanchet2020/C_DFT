#include "dft.h"
#include <math.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  uint32_t N = BUFFER;
  int lines = 0, columns = 0;

  double complex *input = malloc(N * sizeof(double complex));
  double complex *output = NULL;

  for (uint32_t i = 0; i < N; ++i) {
    input[i] = CMPLX(cos(1000 * 2 * M_PI * i / (double)N) +
                         sin(40 * 2 * M_PI * i / (double)N),
                     0);
  }

  output = dft(input, N);

  initscr();
  nodelay(stdscr, TRUE);
  start_color();
  getmaxyx(stdscr, lines, columns);
  // resize_term(lines + 2, columns + 2);

  box(stdscr, 0, 0);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));

  while (getch() != 'q') {
    clear();
    getmaxyx(stdscr, lines, columns);
    uint32_t span = N / (2 * (columns));

    for (uint32_t i = 1; i <= columns; ++i) {
      double avg = 0;
      for (int j = 0; j < span; j++) {
        avg += cabs(output[i * span + j]);
      }

      for (uint32_t j = lines - 5 * avg; j <= lines; j++) {
        //        mvaddch(j, i, '*');
      }
    }

    box(stdscr, 0, 0);
    refresh();
    usleep(10);
  }
  endwin();

  // for (int i = 0; i < columns - 1; ++i) {
  //   double complex avg = 0;
  //   for (int j = 0; j < span; j++){
  //     avg += output[i*span + j];
  //   }

  //   for(int j = lines - 2 - 5 * cabs(avg); j <= lines - 2; j++) mvaddch(j, i,
  //   '*');
  // }

  free(input);
  free(output);

  return 0;
}
