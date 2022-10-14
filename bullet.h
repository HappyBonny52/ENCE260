/** @file   bullet.h
    @author Aaron Sevilla, Bonghyun Kwon
    @date   15 October 2022
    @brief  For controlling bullets's position and state.
*/

#ifndef BULLET_H
#define BULLET_H

#include "player.h"

/* The array state of bullet's staring point */
void spawn_bullet(Player_t *player);

/* The array state of bullet in local funkit and to send the state of outgoing bullet in the other funkit */
void move_self_bullets(void);

/* The array state of bullet in the other funkit that the local player shoot
the array state of player needed to check if the bullet reached the player or not */
void move_outgoing_bullets(Player_t *player);

/* Receive the position of incoming bullet */
void ir_poll_bullets(void);

/* Display player's bullets in matrix */
void display_main_bullets(void);

#endif // !BULLET_H
