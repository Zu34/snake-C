#include "game.h"
#include <stdio.h>
#include <string.h>
#include "time.h"

// Assume these globals are defined elsewhere (game.c or main.c)
extern int snake1_x[], snake1_y[], head1, tail1, dir1_x, dir1_y, score1;
extern int snake2_x[], snake2_y[], head2, tail2, dir2_x, dir2_y, score2;
extern int applex, appley;
extern int powerx, powery;
extern char power_type;
extern int power_timer;
extern int obs_x[], obs_y[], num_obstacles;
extern int speed_boost;
extern int double_score;
extern int lives;

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
    memcpy(s->snake1_x, snake1_x, sizeof(int) * MAX_LEN);
    memcpy(s->snake1_y, snake1_y, sizeof(int) * MAX_LEN);
    s->head1 = head1; s->tail1 = tail1;
    s->dir1_x = dir1_x; s->dir1_y = dir1_y;
    s->score1 = score1;

    memcpy(s->snake2_x, snake2_x, sizeof(int) * MAX_LEN);
    memcpy(s->snake2_y, snake2_y, sizeof(int) * MAX_LEN);
    s->head2 = head2; s->tail2 = tail2;
    s->dir2_x = dir2_x; s->dir2_y = dir2_y;
    s->score2 = score2;

    s->applex = applex; s->appley = appley;
    s->powerx = powerx; s->powery = powery;
    s->power_type = power_type;
    s->power_timer = power_timer;

    memcpy(s->obs_x, obs_x, sizeof(int) * MAX_OBSTACLES);
    memcpy(s->obs_y, obs_y, sizeof(int) * MAX_OBSTACLES);
    s->num_obstacles = num_obstacles;

    s->speed_boost = speed_boost;
    s->double_score = double_score;

    s->lives = lives;
    s->elapsed_time = get_elapsed_seconds();
}

void restore_game_state(GameState *s) {
    memcpy(snake1_x, s->snake1_x, sizeof(int) * MAX_LEN);
    memcpy(snake1_y, s->snake1_y, sizeof(int) * MAX_LEN);
    head1 = s->head1; tail1 = s->tail1;
    dir1_x = s->dir1_x; dir1_y = s->dir1_y;
    score1 = s->score1;

    memcpy(snake2_x, s->snake2_x, sizeof(int) * MAX_LEN);
    memcpy(snake2_y, s->snake2_y, sizeof(int) * MAX_LEN);
    head2 = s->head2; tail2 = s->tail2;
    dir2_x = s->dir2_x; dir2_y = s->dir2_y;
    score2 = s->score2;

    applex = s->applex; appley = s->appley;
    powerx = s->powerx; powery = s->powery;
    power_type = s->power_type;
    power_timer = s->power_timer;

    memcpy(obs_x, s->obs_x, sizeof(int) * MAX_OBSTACLES);
    memcpy(obs_y, s->obs_y, sizeof(int) * MAX_OBSTACLES);
    num_obstacles = s->num_obstacles;

    speed_boost = s->speed_boost;
    double_score = s->double_score;

    lives = s->lives;

    start_timer(); // Reset timer on load
}
