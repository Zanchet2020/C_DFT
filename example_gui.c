#include "dft.h"
#include <math.h>
#include <raylib.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define IO_BUFFER_SIZE BUFFER_SIZE*4

double complex *input = NULL;
double complex *output = NULL;

uint32_t frames_received = 0;

void musicCallback(void *bufferData, unsigned int frames){
  frames_received = frames;
  for(uint32_t i = 0; i < IO_BUFFER_SIZE; ++i) output[i]=0; /* Zeroing the output buffer */
  float (*audio_channels)[2] = bufferData;
  for (uint32_t i = 0; i < frames; ++i) {
    input[i] = CMPLX((audio_channels[i][0] + audio_channels[i][1])/2.0f, 0);
  }
  dft(output, input, frames_received);
}



int main(int argc, char *argv[]) {
  int lines = 0, columns = 0;
  if(argc < 2) {
    printf("ERROR: Provide an audio file\n");
    return -1;
  }else if(argc > 2) {
    printf("ERROR: Unkown args\n");
    return -1;
  }
  
  // INITIALIZING RAYAUDIO
  InitAudioDevice();

  SetAudioStreamBufferSizeDefault(IO_BUFFER_SIZE);
  Music music = LoadMusicStream(argv[1]);
  SetAudioStreamVolume(music.stream, 1.0f);
  AttachAudioStreamProcessor(music.stream, musicCallback);
  PlayMusicStream(music);

  // INITIALIZING NCURSES
  initscr();
  nodelay(stdscr, TRUE);
  start_color();
  curs_set(FALSE);
  getmaxyx(stdscr, lines, columns);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  attron(COLOR_PAIR(1));

  input = malloc(IO_BUFFER_SIZE * sizeof(double complex));
  output = malloc(IO_BUFFER_SIZE * sizeof(double complex));
  double *final_vector = calloc(sizeof(double), IO_BUFFER_SIZE/2);
  
  box(stdscr, 0, 0);
  while(getch() != 'q'){
    UpdateMusicStream(music);
    getmaxyx(stdscr, lines, columns);
    box(stdscr, 0, 0);

    // Calculating velocity and updating final_vector
    for(size_t i = 0; i < IO_BUFFER_SIZE/2; ++i){
      double speed = cabs(output[i])*2 - final_vector[i];
      final_vector[i] += speed * 1.0f;
    }
    

    for (uint32_t i = 1; i < columns - 1; ++i) {
      uint32_t span = ((double)frames_received) / ((double)columns);
      mvprintw(4,5, "div: %.4f", ((double)frames_received) / ((double)columns));
      double avg = 0;
      if(2*i*span > IO_BUFFER_SIZE) continue;
      for (int j = 0; j < span; j++) {
        avg += final_vector[i*span + j]; //cabs(output[i * span + j]);
      }
      avg /= (double)span;
      avg *= 1*cexp(i/4000.0);
      //avg = log((double)i) * avg;
      for (uint32_t j = 1; j < lines - 1; j++) {
        if (j >= lines - 500 * avg && j < lines - 1){
	  //int a = L'\u2588';
          mvaddch(j, i, '|');
	}
        else
          mvaddch(j, i, ' ');
      }
      mvprintw(1,5,"span: %d", span);
    }
    mvprintw(2,5, "frames_received: %d", frames_received);
    mvprintw(3,5, "columns: %d", columns);
    refresh();
    usleep(50);
  }

  endwin();
  DetachAudioStreamProcessor(music.stream, musicCallback);
  UnloadMusicStream(music);
  CloseAudioDevice();
  free(input);
  free(output);

  return 0;
}
