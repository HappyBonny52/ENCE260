/** @file   displays.h
    @author Aaron Sevilla, ase89 
    @author Bonghyun Kwon, bkw31
    @date   15 October 2022
    @brief  Displaying game states
*/

#ifndef displays_H
#define displays_H

#include "player.h"
#include <stdbool.h>

#define PACER_RATE 500
#define MESSAGE_RATE 30
#define MAX_SCORE 3
#define MIN_SCORE 0
#define MESSAGE_LENGTH 4


/* Initialise tinygl and display. */
void displays_init(void);

/** Display a dot used for player, self bullet, outgoing bullets 
    @param x To display entity's position in x axis 
    @param y To display entity's position in y axis  */  
void display_entity(int8_t x, int8_t y);

/* Display the start of the game */
void display_intro(void);

/** Collecting score in order to identify proper display of each state 
   @param win if win is true, acculmulate win_score else accumulate lose_score and if either reaches three, display_result else display_state 
   @note: display_result and display_state are only called within this function
   and nowhere else in the project so they should be private */
void display_end_round(bool);


#endif // !displays_H
