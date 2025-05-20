
#include "player.h"
#include "render.h"
#include "apple.h"
#include "score.h"
#include "position.h"
#include <stdlib.h>

#define POWERUP_DURATION 50

static int power_timer = 0;

void init_player(Player *p, int start_x, int start_y, int xdir, int ydir, int id) {
    p->head = p->tail = 0;
    p->x[0] = start_x;
    p->y[0] = start_y;
    p->xdir = xdir;
    p->ydir = ydir;
    p->score = 0;
    p->id = id;
    draw_snake_head(start_x, start_y, id);
}

void teleport_player(Player *p) {
    int tx, ty;
    do {
        tx = rand() % COLS;
        ty = rand() % ROWS;
    } while (position_in_snake((Position){tx, ty}, p->x, p->head, p->tail) || is_obstacle(tx, ty));
    p->x[p->head] = tx;
    p->y[p->head] = ty;
}

void shrink_player(Player *p) {
    // Shrink player 
    if (p->head != p->tail) {
        p->tail = (p->tail + 1) % MAX_LEN;
    }
}


void move_player(Player *p, Player *opponent) {
    if (p->frozen_turns > 0) {
        p->frozen_turns--;
        // Skip move if frozen
        return;
    }

    clear_tail(p->x[p->tail], p->y[p->tail]);

    int newhead = (p->head + 1) % MAX_LEN;
    p->x[newhead] = (p->x[p->head] + p->xdir + COLS) % COLS;
    p->y[newhead] = (p->y[p->head] + p->ydir + ROWS) % ROWS;

    if (position_in_snake((Position){p->x[newhead], p->y[newhead]}, p->x, p->head, p->tail))
        gameover = 1;


    if (position_in_snake((Position){p->x[newhead], p->y[newhead]}, opponent->x, opponent->head, opponent->tail))
        gameover = 1;

 
    if (is_obstacle(p->x[newhead], p->y[newhead]))
        gameover = 1;

    if (check_apple_collision(p->x[newhead], p->y[newhead], applex, appley)) {
        applex = -1;
        increase_score();
        p->score += double_score ? 2 : 1;
        display_score();
    } else {
        p->tail = (p->tail + 1) % MAX_LEN;
    }

    if (p->x[newhead] == powerx && p->y[newhead] == powery) {
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
    draw_snake_head(p->x[p->head], p->y[p->head], p->id);
}
