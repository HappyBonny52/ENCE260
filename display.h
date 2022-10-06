#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"

void display_init(void);
void display_player(Player_t* player);
void display_dot(int8_t x, int8_t y);
void clear_row(int8_t x);

#endif // !DISPLAY_H
