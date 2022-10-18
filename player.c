/** @file   player.c
    @author Aaron Sevilla, ase89 
    @date   5 October 2022
    @brief  Control player's position and state.
    @note   Columns and rows are swapped from the datasheet model as the game is designed for the funkit to be played sideways.
*/
#include <stdio.h>
#include <stdint.h>
#include "player.h"
#include "bullet.h"
#include "navswitch.h"

/** Initialize player's position.
    @param xpos pixel row
    @param ypos pixel column
    @return player's position in matrix  */
Player_t player_init (int8_t xpos, int8_t ypos) {
    return (Player_t) {.xpos = xpos, .ypos = ypos};
}

/** The pixel state of player moving vertical.
    @param direction 1 for player moves one row down and -1 for player moves one row up
    @param player get the position of player to control x axis movement
    @note The 'rows' here are also in reverse order such that the row closest to the nav switch is considered 0 while the furthest row is considered 5. */
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
    if (player->ypos > BOARDHEIGHT - 2) {
        player->ypos = BOARDHEIGHT - 2;
    }
    if (player->ypos < 0) {
        player->ypos = 0;
    }
}

/* Set the player's action by naviswitch event */
Action_e navswitch_poll(void) {
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        return (Action_e) left;
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        return (Action_e) right;
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        return (Action_e) down;
    }
    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        return (Action_e) up;
    }
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        return (Action_e) attack;
    }
    return (Action_e) null;
}

/** Player handler for each action 
    @param player Player to be handled 
    @param action To indicate what action to be conducted on player  */ 
void handle_player(Player_t *player, Action_e action) {
    switch (action) {
        case left:
            move_x_pos(-1, player);
            break;
        case right:
            move_x_pos(1, player);
            break;
        case down:
            move_y_pos(-1, player);
            break;
        case up:
            move_y_pos(1, player);
            break;
        case attack:
            spawn_bullet(player);
            break;
        default:
            break;
    }
}
