#ifndef BULLET_H
#define BULLET_H

#include "player.h"

void spawn_bullet(Player_t *player);

void move_self_bullets(void);

void move_outgoing_bullets(Player_t *player);

void display_main_bullets(void);

void ir_poll_bullets(void);

#endif // !BULLET_H
