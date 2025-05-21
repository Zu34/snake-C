#include "game_utils.h"
#include "render.h"   
#include <string.h>
#include <ncurses.h>
#include "position.h"
#include "player.h"
#define MAX_OBSTACLES 20

extern int obsx[MAX_OBSTACLES], obsy[MAX_OBSTACLES], num_obstacles;

void draw_obstacle(int x, int y) {
    mvaddch(y, x, '#');
}


void draw_powerup(int x, int y, int power_type) {
    char symbol;
    switch (power_type) {
        case 'S': symbol = '>'; break;
        case 'D': symbol = '$'; break;
        case 'F': symbol = '!'; break;
        case 'T': symbol = '@'; break;
        case 'R': symbol = '-'; break;
        default: symbol = '?'; break;
    }
    mvaddch(y, x, symbol);
}

int check_apple_collision(int x, int y, int applex, int appley) {
    return x == applex && y == appley;
}

void show_status(const char *status) {
    mvprintw(0, 0, "STATUS: %s", status);
    clrtoeol();
}

int position_in_snake(Position pos, Position *snake, int head, int tail) {
    int i = tail;
    while (i != head) {
        if (snake[i].x == pos.x && snake[i].y == pos.y)
            return 1;
        i = (i + 1) % MAX_LEN;
    }
    // Check head position too
    if (snake[head].x == pos.x && snake[head].y == pos.y)
        return 1;
    return 0;
}

int is_obstacle(int x, int y) {
    for (int i = 0; i < num_obstacles; i++) {
        if (obsx[i] == x && obsy[i] == y) {
            return 1;
        }
    }
    return 0;
}
