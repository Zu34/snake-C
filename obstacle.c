#include "render.h"
#include <stdlib.h>
#include <time.h>

#define MAX_OBSTACLES 20
static int ox[MAX_OBSTACLES];
static int oy[MAX_OBSTACLES];
static int num_obstacles = 0;



void init_obstacles() {
    srand(time(NULL));
    num_obstacles = 10 + rand() % 6;  // 10 to 15 obstacles
    for (int i = 0; i < num_obstacles; i++) {
        ox[i] = rand() % COLS;
        oy[i] = rand() % ROWS;
    }
}

void draw_obstacles() {
    for (int i = 0; i < num_obstacles; i++) {
        draw_tile(ox[i], oy[i], '#');  // wall character
    }
}

int is_obstacle(int x, int y) {
    for (int i = 0; i < num_obstacles; i++)
        if (ox[i] == x && oy[i] == y)
            return 1;
    return 0;
}
