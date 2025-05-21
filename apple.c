#include <stdlib.h>
#include <ncurses.h>
#include "game.h"
#include "render.h"
#include "apple.h"
#include "game_utils.h"
#include "position.h"


#define MAX_LEN 1000 

static Position apple;

int positions_equal(Position a, Position b) {
    return a.x == b.x && a.y == b.y;
}

int position_in_obstacles(Position pos, Position *obs, int count) {
    for (int i = 0; i < count; i++) {
        if (positions_equal(obs[i], pos))
            return 1;
    }
    return 0;
}

void spawn_apple(Player *p1, Player *p2, Position obstacles[], int num_obstacles, Position *apple) {
    int valid = 0;
    while (!valid) {
        apple->x = rand() % COLS;
        apple->y = rand() % ROWS;
        valid = 1;

        if (position_in_snake(*apple, p1->body, p1->head, p1->tail)) valid = 0;
        if (position_in_snake(*apple, p2->body, p2->head, p2->tail)) valid = 0;

        for (int i = 0; i < num_obstacles; i++) {
            if (obstacles[i].x == apple->x && obstacles[i].y == apple->y) {
                valid = 0;
                break;
            }
        }
    }

    draw_apple(apple->x, apple->y);
}



Position get_apple_position() {
    return apple;
}
