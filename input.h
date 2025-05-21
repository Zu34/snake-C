#ifndef INPUT_H
#define INPUT_H
#include <termios.h>

static struct termios oldt;

void enable_raw_mode();
void disable_raw_mode();
int kbhit();
int process_input(int *xdir, int *ydir, int *quit);
int process_input_multi(int *xdir1, int *ydir1, int *xdir2, int *ydir2, int *quit, int *paused);


#endif
