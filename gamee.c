#include "score.h"
#include "render.h" 
#include "game.h"
#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define MAX_LEN 1000

// Snake 1
static int x1[MAX_LEN], y1[MAX_LEN];
static int head1 = 0, tail1 = 0;
static int xdir1 = 1, ydir1 = 0;

// Snake 2
static int x2[MAX_LEN], y2[MAX_LEN];
static int head2 = 0, tail2 = 0;
static int xdir2 = -1, ydir2 = 0;

static int applex = -1, appley = -1;
static int gameover = 0;
static int quit = 0;

void init_game() {
    srand(time(NULL));

    // Player 1 starts center-left
    head1 = tail1 = 0;
    x1[head1] = COLS / 3;
    y1[head1] = ROWS / 2;
    xdir1 = 1; ydir1 = 0;

    // Player 2 starts center-right
    head2 = tail2 = 0;
    x2[head2] = COLS * 2 / 3;
    y2[head2] = ROWS / 2;
    xdir2 = -1; ydir2 = 0;

    applex = -1;
    gameover = 0;
    quit = 0;

    draw_border();
    start_timer();
    reset_score();
    display_score();
}

void move_snake(int *x, int *y, int *head, int *tail, int xdir, int ydir) {
    if (x[*head] == applex && y[*head] == appley) {
        applex = -1;
        increase_score();
        display_score();
        display_time();
    } else {
        clear_tail(x[*tail], y[*tail]);
        *tail = (*tail + 1) % MAX_LEN;
    }

    int newhead = (*head + 1) % MAX_LEN;
    x[newhead] = (x[*head] + xdir + COLS) % COLS;
    y[newhead] = (y[*head] + ydir + ROWS) % ROWS;
    *head = newhead;

    draw_snake_head(x[*head], y[*head]);
}

int check_collision(int *x, int *y, int head, int tail, int tx, int ty) {
    for (int i = tail; i != head; i = (i + 1) % MAX_LEN)
        if (x[i] == tx && y[i] == ty)
            return 1;
    return 0;
}

void run_game_loop() {
    while (!quit && !gameover) {
        if (applex < 0)
            spawn_apple(x1, y1, head1, tail1, &applex, &appley);

        move_snake(x1, y1, &head1, &tail1, xdir1, ydir1);
        move_snake(x2, y2, &head2, &tail2, xdir2, ydir2);

        // Self collision
        if (check_collision(x1, y1, head1, tail1, x1[head1], y1[head1]) ||
            check_collision(x2, y2, head2, tail2, x2[head2], y2[head2]))
            gameover = 1;

        // Collision with other snake
        if (check_collision(x1, y1, head1, tail1, x2[head2], y2[head2]) ||
            check_collision(x2, y2, head2, tail2, x1[head1], y1[head1]))
            gameover = 1;

        process_input_multi(&xdir1, &ydir1, &xdir2, &ydir2, &quit);

        usleep(100000 - (get_level() - 1) * 10000); // min 10ms steps
    }

    if (gameover)
        show_game_over();
}
