#ifndef RENDER_H
#define RENDER_H

#include "apple.h"



#define ROWS 30
#define GAME_COLS 60


// ANSI color codes
#define COLOR_RED_TXT    "\e[31m"
#define COLOR_GREEN_TXT  "\e[32m"
#define COLOR_YELLOW_TXT "\e[33m"

// Symbols for snake parts
static const char* snake_head_symbols[] = { "▓", "▓" };
static const char* snake_body_symbols[] = { "█", "█" };
static const char* snake_tail_symbols[] = { "■", "■" };
static const char* apple_symbol = "❤";



void draw_border();
void draw_snake_head(int x, int y, int player_id);
void draw_snake_body(int x, int y, int player_id);
void draw_snake_tail(int x, int y, int player_id);
void clear_cell(int x, int y);
void clear_tail(int x, int y);
void draw_apple(int x, int y);
void show_game_over();

#endif
