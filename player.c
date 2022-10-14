/** @file   player.c
    @author Aaron Sevilla
    @date   5 October 2022
    @brief  Control player's position and state.
*/
#include <stdio.h>
#include <stdint.h>
#include "player.h"


/** Initialize player's position.
    @param xpos pixel row
    @param ypos pixel column
    @return player's position in matrix  */
Player_t player_init (int8_t xpos, int8_t ypos) {
    return (Player_t) {.xpos = xpos, .ypos = ypos};
}


/** The pixel state of player moving vertical.
    @param direction 1 for player moves one row down and -1 for player moves one row up
    @param player get the position of player to control x axis movement*/
void move_x_pos(int8_t direction, Player_t* player) {
    if (direction == 1) {
        player->xpos++;
    }
    if (direction == -1) {
        player->xpos--;
    }
    // When player is off grid wrap to other side on x axis
    if (player->xpos > BOARDWIDTH - 1) {
        player->xpos = 0;
    }
    if (player->xpos < 0) {
        player->xpos = BOARDWIDTH - 1;
    }
}

/** The pixel state of player moving horizontal.
    @param direction 1 for player moves one col up and -1 for player moves one col down
    @param player get the position of player to control y axis movement*/  
void move_y_pos(int8_t direction, Player_t* player) {
    if (direction == 1) {
        player->ypos++;
    }
    if (direction == -1) {
        player->ypos--;
    }
    // Block player from going off grid on y axis
    if (player->ypos > BOARDHEIGHT - 1) {
        player->ypos = BOARDHEIGHT - 1;
    }
    if (player->ypos < 0) {
        player->ypos = 0;
    }
}

