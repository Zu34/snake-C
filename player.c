#include "player.h"
#include "render.h"
#include "apple.h"
#include "score.h"
#include "game.h"
#include "position.h"
#include "game_utils.h"
#include <ncurses.h>
#include <termios.h>
#include <stdlib.h>

// int power_timer = 0;
extern int applex, appley;
extern int gameover;
extern int powerx, powery;
extern char power_type;
extern int power_timer;
extern int speed_boost;
extern int double_score;

void init_player(Player *p, int start_x, int start_y, int xdir, int ydir, int id) {
    p->head = p->tail = 0;
    p->body[0].x = start_x;
    p->body[0].y = start_y;
    p->xdir = xdir;
    p->ydir = ydir;
    p->score = 0;
    p->id = id;
    p->frozen_turns = 0;
    draw_snake_head(start_x, start_y, id);
}

void teleport_player(Player *p) {
    int tx, ty;
    do {
        tx = rand() % COLS;
        ty = rand() % ROWS;
    } while (position_in_snake((Position){tx, ty}, p->body, p->head, p->tail) || is_obstacle(tx, ty));
    p->body[p->head].x = tx;
    p->body[p->head].y = ty;
}

void shrink_player(Player *p) {
    if (p->head != p->tail) {
        p->tail = (p->tail + 1) % MAX_LEN;
    }
}

void move_player(Player *p, Player *opponent) {
    if (p->frozen_turns > 0) {
        p->frozen_turns--;
        return;
    }

    clear_tail(p->body[p->tail].x, p->body[p->tail].y);

    int newhead = (p->head + 1) % MAX_LEN;
    p->body[newhead].x = (p->body[p->head].x + p->xdir + COLS) % COLS;
    p->body[newhead].y = (p->body[p->head].y + p->ydir + ROWS) % ROWS;

    if (position_in_snake(p->body[newhead], p->body, p->head, p->tail))
        gameover = 1;

    if (position_in_snake(p->body[newhead], opponent->body, opponent->head, opponent->tail))
        gameover = 1;

    if (is_obstacle(p->body[newhead].x, p->body[newhead].y))
        gameover = 1;

    if (check_apple_collision(p->body[newhead].x, p->body[newhead].y, applex, appley)) {
        applex = -1;
        increase_score();
        p->score += double_score ? 2 : 1;
        display_score();
    } else {
        p->tail = (p->tail + 1) % MAX_LEN;
    }

    if (p->body[newhead].x == powerx && p->body[newhead].y == powery) {
        switch (power_type) {
            case 'S': speed_boost = 1; break;
            case 'D': double_score = 1; break;
            case 'F': opponent->frozen_turns = 5; break;
            case 'T': teleport_player(p); break;
            case 'R': shrink_player(opponent); break;
        }
        powerx = -1;
    }

    p->head = newhead;
    draw_snake_head(p->body[p->head].x, p->body[p->head].y, p->id);
}
int check_collision(Position pos, Player *p) {
    int i = p->tail;
    while (i != p->head) {
        if (p->body[i].x == pos.x && p->body[i].y == pos.y)
            return 1;
        i = (i + 1) % MAX_LEN;
    }
    // Check head too
    if (p->body[p->head].x == pos.x && p->body[p->head].y == pos.y)
        return 1;
    return 0;
}