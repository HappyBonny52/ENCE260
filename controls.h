/** @file   controls.h
    @author Aaron Sevilla, ase89 
    @date   5 October 2022
    @brief  Control player's position and state by naviswith
*/

#ifndef CONTROLS_H
#define CONTROLS_H

#include "player.h"

/** Actions to be used by naviswitch  */
typedef enum Action_e {
    null,
    left,
    down,
    right,
    up,
    attack,
} Action_e;

/* Set the player's action by naviswitch event */
Action_e navswitch_poll(void);

/** Player handler for each action 
    @param player Player to be handled 
    @param action To indicate what action to be conducted on player  */ 
void handle_player(Player_t *player, Action_e action);

#endif // !CONTROLS_H
