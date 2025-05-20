#ifndef GAMESTATE_H
#define GAMESTATE_H

#define MAX_LEN 1000
#define MAX_OBSTACLES 20

typedef struct {
    int x1[MAX_LEN], y1[MAX_LEN];
    int head1, tail1, xdir1, ydir1, score1;

    int x2[MAX_LEN], y2[MAX_LEN];
    int head2, tail2, xdir2, ydir2, score2;

    int applex, appley;
    int powerx, powery;
    char power_type;
    int power_timer;

    int obsx[MAX_OBSTACLES], obsy[MAX_OBSTACLES];
    int num_obstacles;

    int speed_boost;
    int double_score;
    int lives;

    int elapsed_time;
} GameState;

void save_game_state(GameState *state);
int load_game_state(GameState *state);
void fill_game_state(GameState *state);
void restore_game_state(GameState *state);

#endif
