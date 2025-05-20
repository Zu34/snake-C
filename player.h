
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_LEN 1000
extern int applex, appley;
typedef struct {
    int x[MAX_LEN];
    int y[MAX_LEN];
    int head;
    int tail;
    int xdir;
    int ydir;
    int score;
    int id;  
} Player;

void init_player(Player *p, int start_x, int start_y, int xdir, int ydir, int id);
void move_player(Player *p, Player *opponent);
#endif
