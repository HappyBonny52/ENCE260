/** @file   controls.c
    @author Aaron Sevilla, ase89 
    @date   5 October 2022
    @brief  Control player's position and state by naviswith
*/

#include "controls.h"
#include "navswitch.h"
#include "bullet.h"

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

/* Player handler for each action */
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
