/** @file   display_main.h
    @author Aaron Sevilla, Bonghyun Kwon
    @date   15 October 2022
    @brief  Displaying game state
*/

#ifndef DISPLAY_MAIN_H
#define DISPLAY_MAIN_H

#include "player.h"
#include <stdbool.h>

/* Initialise tinygl and display. */
void display_main_init(void);

void display_entity(int8_t x, int8_t y);

/* Display the start of the game */
void display_intro(void);

/* Collecting score in order to identify proper display of each state */
void display_end_round(bool);

/* Display the state of the game in each round*/
/* void display_state(void);  */

/* Display the result of the game */
/* void display_result(void);  */

void poll_winner(void);

#endif // !DISPLAY_MAIN_H
