// main.c
#include "game.h"
#include <stdlib.h>
#include <ncurses.h>

int main() {
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo input
    curs_set(FALSE);        // Hide cursor
    keypad(stdscr, TRUE);   // Enable arrow keys
    nodelay(stdscr, TRUE);  // Non-blocking getch()

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Player 1
        init_pair(2, COLOR_RED, COLOR_BLACK);    // Player 2
        init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Apple / Powerups
    }

    init_game();            
    run_game_loop();      

    endwin();              

    return EXIT_SUCCESS;
}
