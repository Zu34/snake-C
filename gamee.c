#include "game.h"
#include "score.h"
#include "render.h"
#include "player.h"
#include "input.h"
#include "game_utils.h"
#include <ncurses.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "apple.h"
#include "time_utils.h"


static Position apple;

// Global variable definitions
Player player1;
Player player2;

int applex = -1, appley = -1;
int powerx = -1, powery = -1;
char power_type = 0;
int power_timer = 0;

int obsx[MAX_OBSTACLES], obsy[MAX_OBSTACLES];
Position obstacles[MAX_OBSTACLES];
int num_obstacles = 0;

int gameover = 0;
int quit = 0;
int paused = 0;
int speed_boost = 0;
int double_score = 0;

void init_obstacles() {
    num_obstacles = 5;
    for (int i = 0; i < num_obstacles; i++) {
        obsx[i] = rand() % COLS;
        obsy[i] = rand() % ROWS;
        draw_obstacle(obsx[i], obsy[i]);
    }
}

void init_game() {
    srand(time(NULL));  // Init random seed
    initscr;
    get_score();
    init_obstacles();
    init_player(&player1, 5, 5, 1, 0, 1);
    init_player(&player2, COLS - 5, ROWS - 5, -1, 0, 2);
    spawn_apple(&player1, &player2, obstacles, num_obstacles, &apple);
}



// Remove first spawn_powerup, keep only this one:
void spawn_powerup() {
    if (powerx >= 0) return;  // Power-up already active
    if (rand() % 10 < 7) return;  // ~30% chance to spawn

    powerx = rand() % COLS;
    powery = rand() % ROWS;

    char power_types[] = {'S', 'D', 'F', 'T', 'R'};
    power_type = power_types[rand() % 5];

    draw_powerup(powerx, powery, power_type);
    power_timer = POWERUP_DURATION;
}

void run_game_loop() {
    
    init_player(&player1, /*start_x=*/5, /*start_y=*/5, /*xdir=*/1, /*ydir=*/0, /*id=*/1);
    init_player(&player2, /*start_x=*/COLS - 5, /*start_y=*/ROWS - 5, /*xdir=*/-1, /*ydir=*/0, /*id=*/2);

    spawn_apple(&player1, &player2, obstacles, num_obstacles, &apple);

    while (!quit && !gameover) {
        process_input_multi(&player1.xdir, &player1.ydir, &player2.xdir, &player2.ydir, &quit, &paused);

        if (paused) {
            show_status("PAUSED");
            usleep(150000);
            continue;
        }

        if (apple.x < 0) {
            spawn_apple(&player1, &player2, obstacles, num_obstacles, &apple);
        }

        spawn_powerup();

        move_player(&player1, &player2);
        move_player(&player2, &player1);

        display_score();
        printf("\033[F");  
        display_time();
        fflush(stdout);

        if (power_timer > 0) power_timer--;
        else { speed_boost = 0; double_score = 0; }

        usleep(speed_boost ? 60000 : 100000);
    }

    if (gameover) {
        show_game_over();
        printf("Final Score: P1=%d P2=%d\n", player1.score, player2.score);
        getchar();
    }
}
