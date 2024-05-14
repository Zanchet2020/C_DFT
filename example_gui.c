#include "dft.h"
#include <math.h>
#include <raylib.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  uint32_t N = BUFFER;
  int lines = 0, columns = 0;

  if(argc < 2) {
    printf("ERROR: Provide an audio file\n");
    return -1;
  }else if(argc > 2) {
    printf("ERROR: Unkown args\n");
    return -1;
  }

  initscr();
  nodelay(stdscr, TRUE);
  start_color();
  getmaxyx(stdscr, lines, columns);

  double complex *input = malloc(N * sizeof(double complex));
  double complex *output = malloc(N * sizeof(double complex));

  // for (uint32_t i = 0; i < N; ++i) {
  //   input[i] = CMPLX(cos(1000 * 2 * M_PI * i / (double)N) +
  //                        sin(40 * 2 * M_PI * i / (double)N),
  //                    0);
  // }

  // getch();
  // resize_term(lines + 2, columns + 2);
  Wave audio = LoadWave(argv[1]);
  // uint64_t rawSize = audio.frameCount * (audio.sampleSize / 8) * audio.channels;
  float (*audio_channels)[2] = audio.data;

  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));

  box(stdscr, 0, 0);
  for (size_t start_frame = 0; start_frame < audio.frameCount; start_frame += N) {
    if (getch() == 'q')
      break;
    for (uint32_t i = 0; i < N; ++i) {
      // input[i] = CMPLX(cos(100 * ((double)i/(double)N) * PI),0);
      input[i] = CMPLX((audio_channels[start_frame + i][0] + audio_channels[start_frame + i][1])/2.0f, 0);
    }
    dft(output, input, N);
    getmaxyx(stdscr, lines, columns);
    box(stdscr, 0, 0);
    uint32_t span = N / (2 * (columns));

    for (uint32_t i = 1; i < columns - 1; ++i) {
      double avg = 0;
      for (int j = 0; j < span; j++) {
        avg += cabs(output[i * span + j]);
      }
      avg /= span;
      for (uint32_t j = 1; j < lines - 1; j++) {
        if (j >= lines - 250 * avg && j < lines - 1)
          mvaddch(j, i, '*');
        else
          mvaddch(j, i, ' ');
      }
    }
    refresh();
    //    usleep(1);
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
  UnloadWave(audio);
  free(input);
  free(output);

  return 0;
}
