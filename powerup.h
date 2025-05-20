#ifndef POWERUP_H
#define POWERUP_H

void spawn_powerup(void);
void draw_powerup(void);
int check_powerup_collision(int x, int y);
void update_powerup_state(void);
int is_speed_boost_active(void);
int is_double_score_active(void);

#endif
