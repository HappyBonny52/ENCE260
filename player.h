/** @file   player.h
    @author Aaron Sevilla
    @date   5 October 2022
    @brief  Control player's position and state.
    @note Player use x axis for row and y axis for column
          and automatically change its state when it trespass the boundary
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#define BOARDWIDTH 7  // in x axis
#define BOARDHEIGHT 5 // in y axis 

/* Player state structure.  */
typedef struct Player_t {
    int8_t xpos;
    int8_t ypos;
} Player_t;

/* Initialize player's position.*/
Player_t player_init (int8_t xpos, int8_t ypos);

/* The pixel state of player moving vertical.*/
void move_x_pos(int8_t direction, Player_t* player);

/* The pixel state of player moving horizontal.*/
void move_y_pos(int8_t direction, Player_t* player);

#endif // !PLAYER_H
