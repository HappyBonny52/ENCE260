#ifndef DISPLAY_MAIN_H
#define DISPLAY_MAIN_H

#include "player.h"
#include <stdbool.h>

void display_main_init(void);
void display_entity(int8_t x, int8_t y);
void display_intro(void);
void display_end_round(bool);
void poll_winner(void);
/* void display_state(void); */
/* void display_result(void); */

#endif // !DISPLAY_MAIN_H
