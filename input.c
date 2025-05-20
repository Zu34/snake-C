#include "input.h"
#include <termios.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>

static struct termios oldt;

void enable_raw_mode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    printf("\e[?25l");
    atexit(disable_raw_mode);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\e[?25h");
}

int kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

int process_input(int *xdir, int *ydir, int *quit) {
    if (!kbhit()) return 0;
    int ch = getchar();
    if (ch == 27 || ch == 'q') {
        *quit = 1;
    } else if (ch == 'h' && *xdir != 1) {
        *xdir = -1; *ydir = 0;
    } else if (ch == 'l' && *xdir != -1) {
        *xdir = 1; *ydir = 0;
    } else if (ch == 'j' && *ydir != -1) {
        *xdir = 0; *ydir = 1;
    } else if (ch == 'k' && *ydir != 1) {
        *xdir = 0; *ydir = -1;
    }
    return 0;
}

int process_input_multi(int *xdir1, int *ydir1, int *xdir2, int *ydir2, int *quit) {
    if (!kbhit()) return 0;
    int ch = getchar();
    extern int paused;
    // Player 1 - HJKL
    if (ch == 'h' && *xdir1 != 1) {
        *xdir1 = -1; *ydir1 = 0;
    } else if (ch == 'l' && *xdir1 != -1) {
        *xdir1 = 1; *ydir1 = 0;
    } else if (ch == 'j' && *ydir1 != -1) {
        *xdir1 = 0; *ydir1 = 1;
    } else if (ch == 'k' && *ydir1 != 1) {
        *xdir1 = 0; *ydir1 = -1;
    }

    // Player 2 - WASD
    else if (ch == 'a' && *xdir2 != 1) {
        *xdir2 = -1; *ydir2 = 0;
    } else if (ch == 'd' && *xdir2 != -1) {
        *xdir2 = 1; *ydir2 = 0;
    } else if (ch == 's' && *ydir2 != -1) {
        *xdir2 = 0; *ydir2 = 1;
    } else if (ch == 'w' && *ydir2 != 1) {
        *xdir2 = 0; *ydir2 = -1;
    }

    if (ch == 'p' || ch == 'P') {
        paused = !paused;
        if (paused) printf("PAUSED\n");
        else printf("RESUMED\n");
        return 0;
    }

    // Quit
    else if (ch == 27 || ch == 'q') {
        *quit = 1;
    }

    return 0;
}

