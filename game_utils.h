#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "position.h"

void draw_obstacle(int x, int y);
void draw_powerup(int x, int y, int power_type);
int check_apple_collision(int x, int y, int applex, int appley);
void show_status(const char *status);
int position_in_snake(Position pos, Position *snake, int head, int tail);
int is_obstacle(int x, int y);

#endif
