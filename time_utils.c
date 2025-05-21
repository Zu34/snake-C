#include "time_utils.h"
#include <time.h>
#include <stdio.h>

static time_t start_time;

void start_timer(void) {
    start_time = time(NULL);
}

int get_elapsed_seconds(void) {
    return (int)(time(NULL) - start_time);
}

void display_time(void) {
    int elapsed = get_elapsed_seconds();
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;

    printf("\033[F");  // move cursor up one line
    printf("\rTime: %02d:%02d\n", minutes, seconds);
    fflush(stdout);
}
