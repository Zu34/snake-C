#ifndef PLAYER_H
#define PLAYER_H

#include "position.h" 

#define MAX_LEN 1000

typedef struct Player {
    Position body[MAX_LEN];
    int head;
    int tail;
    int xdir;
    int ydir;
    int score;
    int id;
    int frozen_turns;
} Player;

// Player function declarations
void init_player(Player *p, int start_x, int start_y, int xdir, int ydir, int id);
void move_player(Player *p, Player *opponent);
void teleport_player(Player *p);
void shrink_player(Player *p);
int check_collision(Position pos, Player *p);
#endif // PLAYER_H
