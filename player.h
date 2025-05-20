
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_LEN 1000

extern int applex, appley;
extern int gameover;
extern int powerx, powery, power_timer;
extern char power_type;
extern int speed_boost, double_score;

typedef struct {
    int x[MAX_LEN];
    int y[MAX_LEN];
    int head;
    int tail;
    int xdir;
    int ydir;
    int score;
    int id;  
    int frozen_turns; 
} Player;

void init_player(Player *p, int start_x, int start_y, int xdir, int ydir, int id);
void move_player(Player *p, Player *opponent);
#endif
