#include "score.h"
#include "render.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "apple.h"

void init_obstacles() {
    num_obstacles = 5;
    for (int i = 0; i < num_obstacles; i++) {
        obsx[i] = rand() % COLS;
        obsy[i] = rand() % ROWS;
        draw_obstacle(obsx[i], obsy[i]);
    }
}

int is_obstacle(int x, int y) {
    for (int i = 0; i < num_obstacles; i++)
        if (obsx[i] == x && obsy[i] == y)
            return 1;
    return 0;
}

void spawn_apple() {
    while (1) {
        int valid = 1;
        applex = rand() % COLS;
        appley = rand() % ROWS;

        for (int i = tail1; i != head1; i = (i + 1) % MAX_LEN)
            if (x1[i] == applex && y1[i] == appley) valid = 0;
        for (int i = tail2; i != head2; i = (i + 1) % MAX_LEN)
            if (x2[i] == applex && y2[i] == appley) valid = 0;
        if (is_obstacle(applex, appley)) valid = 0;

        if (valid) break;
    }
    draw_apple(applex, appley);
}

void spawn_powerup() {
    if (powerx >= 0) return; 
    if (rand() % 10 < 3) return;  // 30% chance

    powerx = rand() % COLS;
    powery = rand() % ROWS;
    power_type = (rand() % 2 == 0) ? 'S' : 'D';
    power_timer = POWERUP_DURATION;
    draw_powerup(powerx, powery, power_type);
}

int check_collision(int x, int y, int *ox, int *oy, int head, int tail) {
    for (int i = tail; i != head; i = (i + 1) % MAX_LEN)
        if (ox[i] == x && oy[i] == y)
            return 1;
    return 0;
}

void move_snake(int *x, int *y, int *head, int *tail,
                int xdir, int ydir, int player_id, int *score) {
    clear_tail(x[*tail], y[*tail]);

    int newhead = (*head + 1) % MAX_LEN;
    x[newhead] = (x[*head] + xdir + COLS) % COLS;
    y[newhead] = (y[*head] + ydir + ROWS) % ROWS;

    // Self collision
    if (check_collision(x[newhead], y[newhead], x, y, *head, *tail))
        gameover = 1;

    // Obstacle collision
    if (is_obstacle(x[newhead], y[newhead]))
        gameover = 1;

    // Cross-snake collision
    if (player_id == 1 && check_collision(x[newhead], y[newhead], x2, y2, head2, tail2))
        gameover = 1;
    if (player_id == 2 && check_collision(x[newhead], y[newhead], x1, y1, head1, tail1))
        gameover = 1;

    // Apple
    if (check_apple_collision(x[newhead], y[newhead], applex, appley)) {
        applex = -1;
        increase_score();
        display_score();
    } else {
        *tail = (*tail + 1) % MAX_LEN;
    }
    
    // Power-up
    if (x[newhead] == powerx && y[newhead] == powery) {
        if (power_type == 'S') speed_boost = 1;
        if (power_type == 'D') double_score = 1;
        powerx = -1;
    }

    *head = newhead;
    draw_snake_head(x[*head], y[*head], player_id);
}

Player player1, player2;

void init_game() {
    srand(time(NULL));
    draw_border();
    init_obstacles();
    init_player(&player1, COLS / 3, ROWS / 2, 1, 0, 1);
    init_player(&player2, 2 * COLS / 3, ROWS / 2, -1, 0, 2);
    applex = -1; powerx = -1;
    reset_score();
    start_timer();
    display_score();
    display_time();
}

void run_game_loop() {
    while (!quit && !gameover) {
        process_input_multi(&player1.xdir, &player1.ydir, &player2.xdir, &player2.ydir, &quit, &paused);

        if (paused) {
            show_status("PAUSED");
            usleep(150000);
            continue;
        }

        if (applex < 0) spawn_apple();
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
