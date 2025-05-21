
#include "input.h"
#include <ncurses.h>

int process_input(int *xdir, int *ydir, int *quit) {
    int ch = getch();
    if (ch == ERR) return 0; 

    switch (ch) {
        case 'q': *quit = 1; break;
        case 'h': if (*xdir != 1) { *xdir = -1; *ydir = 0; } break;
        case 'l': if (*xdir != -1) { *xdir = 1; *ydir = 0; } break;
        case 'j': if (*ydir != -1) { *xdir = 0; *ydir = 1; } break;
        case 'k': if (*ydir != 1) { *xdir = 0; *ydir = -1; } break;
    }
    return 1;
}

int process_input_multi(int *xdir1, int *ydir1, int *xdir2, int *ydir2, int *quit, int *paused) {
    int ch = getch();
    if (ch == ERR) return 0;

    switch (ch) {
        // Player 1 - HJKL
        case 'h': if (*xdir1 != 1) { *xdir1 = -1; *ydir1 = 0; } break;
        case 'l': if (*xdir1 != -1) { *xdir1 = 1; *ydir1 = 0; } break;
        case 'j': if (*ydir1 != -1) { *xdir1 = 0; *ydir1 = 1; } break;
        case 'k': if (*ydir1 != 1) { *xdir1 = 0; *ydir1 = -1; } break;

        // Player 2 - WASD
        case 'a': if (*xdir2 != 1) { *xdir2 = -1; *ydir2 = 0; } break;
        case 'd': if (*xdir2 != -1) { *xdir2 = 1; *ydir2 = 0; } break;
        case 's': if (*ydir2 != -1) { *xdir2 = 0; *ydir2 = 1; } break;
        case 'w': if (*ydir2 != 1) { *xdir2 = 0; *ydir2 = -1; } break;

        // Pause/unpause
        case 'p':
        case 'P':
            *paused = !(*paused);
            break;

        // Quit
        case 'q':
        case 27:
            *quit = 1;
            break;
    }

    return 1;
}
