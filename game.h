#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "position.h"

#define MAX_LEN 1000
#define MAX_OBSTACLES 20
#define POWERUP_DURATION 50

// --- Players ---
extern Player player1;
extern Player player2;

// --- Apple and Power-up state ---
extern int applex, appley;
extern int powerx, powery;
extern char power_type;
extern int power_timer;

// --- Obstacles ---
extern int obsx[MAX_OBSTACLES], obsy[MAX_OBSTACLES];
extern Position obstacles[MAX_OBSTACLES];
extern int num_obstacles;

// --- Game state flags ---
extern int gameover;
extern int quit;
extern int paused;
extern int speed_boost;
extern int double_score;
extern int lives; // Moved here from gamestate.h

// --- Save system ---
typedef struct {
    int snake1_x[MAX_LEN], snake1_y[MAX_LEN];
    int head1, tail1, dir1_x, dir1_y, score1;

    int snake2_x[MAX_LEN], snake2_y[MAX_LEN];
    int head2, tail2, dir2_x, dir2_y, score2;

    int applex, appley;
    int powerx, powery;
    char power_type;
    int power_timer;

    int obs_x[MAX_OBSTACLES], obs_y[MAX_OBSTACLES];
    int num_obstacles;

    int speed_boost;
    int double_score;
    int lives;

    int elapsed_time;
} GameState;

// Game lifecycle
void init_game();
void run_game_loop();


// Save/load
void save_game_state(GameState *state);
int load_game_state(GameState *state);
void fill_game_state(GameState *state);
void restore_game_state(GameState *state);

// Utility
void spawn_apple(Player *p1, Player *p2, Position obstacles[], int num_obstacles, Position *apple);
void spawn_powerup();
int is_obstacle(int x, int y);
void init_obstacles();


#endif
