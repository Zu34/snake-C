#ifndef RENDER_H
#define RENDER_H

#define COLS 60
#define ROWS 30

void draw_border();
void draw_snake_head(int x, int y , int player_id);
void clear_tail(int x, int y);
void spawn_apple(int x[], int y[], int head, int tail, int *ax, int *ay);
void show_game_over();

#endif
