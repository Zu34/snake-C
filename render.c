#include "render.h"
#include <stdio.h>

#define COLS 60
#define ROWS 30

// ANSI color codes
#define COLOR_RED    "\e[31m"
#define COLOR_GREEN  "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_RESET  "\e[0m"

// Symbols for snake parts
static const char* snake_head_symbols[] = { "▓", "▓" };
static const char* snake_body_symbols[] = { "█", "█" };
static const char* snake_tail_symbols[] = { "■", "■" };
static const char* apple_symbol = "❤";

// Draw game border
void draw_border() {
    printf("┌");
    for (int i = 0; i < COLS; i++) printf("─");
    printf("┐\n");

    for (int j = 0; j < ROWS; j++) {
        printf("│");
        for (int i = 0; i < COLS; i++) printf("·");
        printf("│\n");
    }

    printf("└");
    for (int i = 0; i < COLS; i++) printf("─");
    printf("┘\n");
}

// Draw snake head at (x, y) with player color
void draw_snake_head(int x, int y, int player_id) {
    const char* color = (player_id == 1) ? COLOR_GREEN : COLOR_RED;
    printf("\e[%dB\e[%dC%s%s%s", y + 1, x + 1, color, snake_head_symbols[player_id - 1], COLOR_RESET);
    printf("\e[%dF", y + 1);
    fflush(stdout);
}

// Draw snake body part at (x, y) with player color
void draw_snake_body(int x, int y, int player_id) {
    const char* color = (player_id == 1) ? COLOR_GREEN : COLOR_RED;
    printf("\e[%dB\e[%dC%s%s%s", y + 1, x + 1, color, snake_body_symbols[player_id - 1], COLOR_RESET);
    printf("\e[%dF", y + 1);
    fflush(stdout);
}

// Draw snake tail at (x, y) with player color
void draw_snake_tail(int x, int y, int player_id) {
    const char* color = (player_id == 1) ? COLOR_GREEN : COLOR_RED;
    printf("\e[%dB\e[%dC%s%s%s", y + 1, x + 1, color, snake_tail_symbols[player_id - 1], COLOR_RESET);
    printf("\e[%dF", y + 1);
    fflush(stdout);
}

// Clear cell at (x, y)
void clear_cell(int x, int y) {
    printf("\e[%dB\e[%dC·", y + 1, x + 1);
    printf("\e[%dF", y + 1);
    fflush(stdout);
}

// Clear tail cell
void clear_tail(int x, int y) {
    clear_cell(x, y);
}


void draw_apple(int x, int y) {
    printf("\e[%dB\e[%dC%s%s%s", y + 1, x + 1, COLOR_YELLOW, apple_symbol, COLOR_RESET);
    printf("\e[%dF", y + 1);
    fflush(stdout);
}

// Show game over message
void show_game_over() {
    printf("\e[%dB\e[%dC Game Over! Press any key to exit. ", ROWS / 2, COLS / 2 - 10);
    printf("\e[%dF", ROWS / 2);
    fflush(stdout);
}
