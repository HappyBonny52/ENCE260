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

typedef enum Action_e {
    null,
    left,
    down,
    right,
    up,
    attack,
} Action_e;

/** Initialize player's position.
    @param xpos pixel row
    @param ypos pixel column
    @return player's position in matrix  */
Player_t player_init (int8_t xpos, int8_t ypos);

/** The pixel state of player moving vertical.
    @param direction 1 for player moves one row down and -1 for player moves one row up
    @param player get the position of player to control x axis movement
    @note The 'rows' here are also in reverse order such that the row closest to the nav switch is considered 0 while the furthest row is considered 5. */
void move_x_pos(int8_t direction, Player_t* player);

/** The pixel state of player moving horizontal.
    @param direction 1 for player moves one col up and -1 for player moves one col down
    @param player get the position of player to control y axis movement*/  
void move_y_pos(int8_t direction, Player_t* player);

/* Set the player's action by naviswitch event */
Action_e navswitch_poll(void);

/** Player handler for each action 
    @param player Player to be handled 
    @param action To indicate what action to be conducted on player  */ 
void handle_player(Player_t *player, Action_e action);

#endif // !PLAYER_H
