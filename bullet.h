#ifndef BULLET_H
#define BULLET_H

#include "player.h"

void spawn_bullet(Player_t *player);

void move_self_bullets(void);

void move_outgoing_bullets(void);

void display_main_bullets(void);

void ir_poll(void);

#endif // !BULLET_H
