#ifndef DISPLAY_MAIN_H
#define DISPLAY_MAIN_H

#include "player.h"

void display_main_init(void);
void display_main_player(Player_t* player);
/* void display_main_dot(int8_t x, int8_t y); */
void display_entity(int8_t x, int8_t y);
void clear_row(int8_t x);

#endif // !DISPLAY_MAIN_H
