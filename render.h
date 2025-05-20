#ifndef RENDER_H

#define RENDER_H

#define COLS 60
#define ROWS 30

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



void draw_border();
void draw_snake_head(int x, int y , int player_id);
void clear_tail(int x, int y);
void spawn_apple(int x[], int y[], int head, int tail, int *ax, int *ay);
void show_game_over();

#endif
