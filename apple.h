#ifndef APPLE_H
#define APPLE_H
#include "player.h" 
#include "position.h"

void spawn_apple(Player *p1, Player *p2, Position obstacles[], int num_obstacles, Position *apple);

Position get_apple_position();

#endif
