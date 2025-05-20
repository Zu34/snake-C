#include "gamestate.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"


void save_game_state(GameState *state) {
    FILE *f = fopen("save.dat", "wb");
    if (f) {
        fwrite(state, sizeof(GameState), 1, f);
        fclose(f);
    }
}

int load_game_state(GameState *state) {
    FILE *f = fopen("save.dat", "rb");
    if (f) {
        fread(state, sizeof(GameState), 1, f);
        fclose(f);
        return 1;
    }
    return 0;
}

void fill_game_state(GameState *s) {
    memcpy(s->x1, x1, sizeof(int) * MAX_LEN);
    memcpy(s->y1, y1, sizeof(int) * MAX_LEN);
    s->head1 = head1; s->tail1 = tail1;
    s->xdir1 = xdir1; s->ydir1 = ydir1;
    s->score1 = score1;

    memcpy(s->x2, x2, sizeof(int) * MAX_LEN);
    memcpy(s->y2, y2, sizeof(int) * MAX_LEN);
    s->head2 = head2; s->tail2 = tail2;
    s->xdir2 = xdir2; s->ydir2 = ydir2;
    s->score2 = score2;

    s->applex = applex; s->appley = appley;
    s->powerx = powerx; s->powery = powery;
    s->power_type = power_type;
    s->power_timer = power_timer;

    memcpy(s->obsx, obsx, sizeof(int) * MAX_OBSTACLES);
    memcpy(s->obsy, obsy, sizeof(int) * MAX_OBSTACLES);
    s->num_obstacles = num_obstacles;

    s->speed_boost = speed_boost;
    s->double_score = double_score;

    s->lives = lives;
    s->elapsed_time = get_elapsed_seconds();
}

void restore_game_state(GameState *s) {
    memcpy(x1, s->x1, sizeof(int) * MAX_LEN);
    memcpy(y1, s->y1, sizeof(int) * MAX_LEN);
    head1 = s->head1; tail1 = s->tail1;
    xdir1 = s->xdir1; ydir1 = s->ydir1;
    score1 = s->score1;

    memcpy(x2, s->x2, sizeof(int) * MAX_LEN);
    memcpy(y2, s->y2, sizeof(int) * MAX_LEN);
    head2 = s->head2; tail2 = s->tail2;
    xdir2 = s->xdir2; ydir2 = s->ydir2;
    score2 = s->score2;

    applex = s->applex; appley = s->appley;
    powerx = s->powerx; powery = s->powery;
    power_type = s->power_type;
    power_timer = s->power_timer;

    memcpy(obsx, s->obsx, sizeof(int) * MAX_OBSTACLES);
    memcpy(obsy, s->obsy, sizeof(int) * MAX_OBSTACLES);
    num_obstacles = s->num_obstacles;

    speed_boost = s->speed_boost;
    double_score = s->double_score;

    lives = s->lives;
    start_timer();  // reset timer
}
