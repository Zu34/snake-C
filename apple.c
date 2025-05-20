#include <stdlib.h>
#include <ncurses.h>
#include "game.h"
#include "render.h"
#include "apple.h"
#include "position.h"


#define MAX_LEN 1000 

static Position apple;

int positions_equal(Position a, Position b) {
    return a.x == b.x && a.y == b.y;
}

int position_in_snake(Position pos, Position *snake, int head, int tail) {
    for (int i = tail; i != head; i = (i + 1) % MAX_LEN) 
    {
        if (positions_equal(snake[i], pos))
            return 1;
    }
    return 0;
}

int position_in_obstacles(Position pos, Position *obs, int count) {
    for (int i = 0; i < count; i++) {
        if (positions_equal(obs[i], pos))
            return 1;
    }
    return 0;
}

void spawn_apple(Position *apple, Position *snake1, int head1, int tail1,
                 Position *snake2, int head2, int tail2,
                 Position *obstacles, int num_obstacles) {

    Position pos;
    while (1) {
        pos.x = rand() % COLS;
        pos.y = rand() % ROWS;

        if (position_in_snake(pos, snake1, head1, tail1)) continue;
        if (position_in_snake(pos, snake2, head2, tail2)) continue;
        if (position_in_obstacles(pos, obstacles, num_obstacles)) continue;

        break;
    }
    *apple = pos;
    draw_apple(apple->x, apple->y);
}

Position get_apple_position() {
    return apple;
}
