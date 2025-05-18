#include <time.h>
#include "score.h"
#include <stdio.h>

static time_t start_time;
static int score = 0;
static int level = 1;

void reset_score() {
    score = 0;
    level = 1;
}

void increase_score() {
    score++;
    level = score / 5 + 1; // Level increases every 5 points
}

int get_score() {
    return score;
}

int get_level() {
    return level;
}

void display_score() {
    printf("\e[%d;%dHScore: %d | Level: %d", 1, 2, score, level);
    fflush(stdout);
}

void start_timer() {
    start_time = time(NULL);
}

int get_elapsed_seconds() {
    return (int)(time(NULL) - start_time);
}

void display_time() {
    printf("\e[%d;%dHTime: %ds", 2, 2, get_elapsed_seconds());
    fflush(stdout);
}