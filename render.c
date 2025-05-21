

#include "render.h"
#include "game_utils.h"
#include <ncurses.h>

void draw_border() {
    for (int i = 0; i <= COLS + 1; i++) {
        mvaddch(0, i, '-');
        mvaddch(ROWS + 1, i, '-');
    }

    for (int j = 1; j <= ROWS; j++) {
        mvaddch(j, 0, '|');
        for (int i = 1; i <= COLS; i++) {
            mvaddch(j, i, '.');  // background dots
        }
        mvaddch(j, COLS + 1, '|');
    }

    refresh();
}

void draw_snake_head(int x, int y, int player_id) {
    attron(COLOR_PAIR(player_id));
    mvprintw(y + 1, x + 1, "%s", snake_head_symbols[player_id - 1]);
    attroff(COLOR_PAIR(player_id));
}

void draw_snake_body(int x, int y, int player_id) {
    attron(COLOR_PAIR(player_id));
    mvprintw(y + 1, x + 1, "%s", snake_body_symbols[player_id - 1]);
    attroff(COLOR_PAIR(player_id));
}

void draw_snake_tail(int x, int y, int player_id) {
    attron(COLOR_PAIR(player_id));
    mvprintw(y + 1, x + 1, "%s", snake_tail_symbols[player_id - 1]);
    attroff(COLOR_PAIR(player_id));
}

void clear_cell(int x, int y) {
    mvprintw(y + 1, x + 1, ".");
}

void clear_tail(int x, int y) {
    clear_cell(x, y);
}

void draw_apple(int x, int y) {
    attron(COLOR_PAIR(3));
    mvprintw(y + 1, x + 1, "%s", apple_symbol);
    attroff(COLOR_PAIR(3));
}

void show_game_over() {
    int x = COLS / 2 - 10;
    int y = ROWS / 2;
    mvprintw(y, x, "Game Over! Press any key.");
    refresh();
}
