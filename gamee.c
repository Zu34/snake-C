#include "score.h"
#include "render.h"
#include "game.h"
#include "input.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define MAX_LEN 1000

// S1
static int x1[MAX_LEN], y1[MAX_LEN];
static int head1 = 0, tail1 = 0;
static int xdir1 = 1, ydir1 = 0;

// S2
static int x2[MAX_LEN], y2[MAX_LEN];
static int head2 = 0, tail2 = 0;
static int xdir2 = -1, ydir2 = 0;

// Apple
static int applex = -1, appley = -1;

static int gameover = 0;
static int quit = 0;

void init_game() {
    srand(time(NULL));
    head1 = tail1 = 0;
    x1[head1] = COLS / 3;
    y1[head1] = ROWS / 2;

    head2 = tail2 = 0;
    x2[head2] = 2 * COLS / 3;
    y2[head2] = ROWS / 2;

    xdir1 = 1; ydir1 = 0;
    xdir2 = -1; ydir2 = 0;
    applex = -1;

    draw_border();
    start_timer();
    reset_score();
    display_score();
    display_time();
}

void spawn_apple(int *x1, int *y1, int head1, int tail1,
                 int *x2, int *y2, int head2, int tail2,
                 int *ax, int *ay) {
    while (1) {
        int valid = 1;
        *ax = rand() % COLS;
        *ay = rand() % ROWS;

        for (int i = tail1; i != head1; i = (i + 1) % MAX_LEN)
            if (x1[i] == *ax && y1[i] == *ay) valid = 0;
        for (int i = tail2; i != head2; i = (i + 1) % MAX_LEN)
            if (x2[i] == *ax && y2[i] == *ay) valid = 0;

        if (valid) break;
    }

    draw_apple(*ax, *ay);
}

void move_snake(int *x, int *y, int *head, int *tail,
                int xdir, int ydir, int *ax, int *ay, int player_id) {
    clear_tail(x[*tail], y[*tail]);

    int newhead = (*head + 1) % MAX_LEN;
    x[newhead] = (x[*head] + xdir + COLS) % COLS;
    y[newhead] = (y[*head] + ydir + ROWS) % ROWS;
    *head = newhead;

    // Check collision with self
    for (int i = *tail; i != *head; i = (i + 1) % MAX_LEN)
        if (x[i] == x[*head] && y[i] == y[*head])
            gameover = 1;

    // Check for apple
    if (x[*head] == *ax && y[*head] == *ay) {
        *ax = -1;
        increase_score();
        display_score();
        display_time();
    } else {
        *tail = (*tail + 1) % MAX_LEN;
    }

    draw_snake_head(x[*head], y[*head], player_id);
}

void run_game_loop() {
    while (!quit && !gameover) {
        if (applex < 0)
            spawn_apple(x1, y1, head1, tail1, x2, y2, head2, tail2, &applex, &appley);

        // Move snakes
        move_snake(x1, y1, &head1, &tail1, xdir1, ydir1, &applex, &appley, 1);
        move_snake(x2, y2, &head2, &tail2, xdir2, ydir2, &applex, &appley, 2);

        // input
        process_input_multi(&xdir1, &ydir1, &xdir2, &ydir2, &quit);

        usleep(100000 - (get_level() - 1) * 10000);
    }

    if (gameover) {
        show_game_over();
        getchar(); 
    }
}
