#ifndef GAME_H
#define GAME_H

#define MAX_LEN 1000
#define MAX_LEN 1000
#define MAX_OBSTACLES 20
#define POWERUP_DURATION 50

static int x1[MAX_LEN], y1[MAX_LEN];

// Snake1
static int head1 = 0, tail1 = 0;
static int xdir1 = 1, ydir1 = 0;
static int score1 = 0;

// Snake2
static int x2[MAX_LEN], y2[MAX_LEN];
static int head2 = 0, tail2 = 0;
static int xdir2 = -1, ydir2 = 0;
static int score2 = 0;

// Apple & Power-ups
static int applex = -1, appley = -1;
static int powerx = -1, powery = -1;
static char power_type = 0;  // 'S' or 'D'
static int power_timer = 0;

// Obstacles
static int obsx[MAX_OBSTACLES], obsy[MAX_OBSTACLES];
static int num_obstacles = 0;

static int gameover = 0;
static int quit = 0;
static int paused = 0;
static int speed_boost = 0;
static int double_score = 0;

extern int speed_boost, double_score;
static int power_timer = 0;


typedef struct {
    int x[MAX_LEN];
    int y[MAX_LEN];
    int head;
    int tail;
    int xdir;
    int ydir;
    int score;
    int id;
    int frozen_turns;  // Make sure this exists!
} Player;


void init_game();
void run_game_loop();

#endif
