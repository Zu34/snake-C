#include "render.h"
#include <stdlib.h>
#include <time.h>

static int px = -1, py = -1;
static char ptype = 0;
static int timer = 0;

void spawn_powerup() {
    if (rand() % 50 == 0 && px == -1) {
        px = rand() % COLS;
        py = rand() % ROWS;
        ptype = (rand() % 2) ? 'S' : 'D'; // S = speed, D = double
    }
}

void draw_powerup() {
    if (px != -1) draw_tile(px, py, ptype);
}

int check_powerup_collision(int x, int y) {
    if (x == px && y == py) {
        timer = 50;
        char collected = ptype;
        px = -1; py = -1;
        return collected;
    }
    return 0;
}

void update_powerup_state() {
    if (timer > 0) timer--;
}

int is_speed_boost_active() { return (ptype == 'S' && timer > 0); }
int is_double_score_active() { return (ptype == 'D' && timer > 0); }
