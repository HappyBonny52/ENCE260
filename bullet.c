/** @file   bullet.c
    @author Aaron Sevilla, ase89 
    @author Bonghyun Kwon, bkw31
    @date   15 October 2022
    @brief  Control bullets's position and state.
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bullet.h"
#include "displays.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "system.h"
#include "pio.h"

#define WIN_SIGNAL '!'

// Array of bullets where values are x axes and index is y axes
static uint8_t self_bullets[BOARDHEIGHT + 1] = {0};
static uint8_t outgoing_bullets[BOARDHEIGHT + 1] = {0};

/** The array state of bullet's staring point
    @param player To get the state of player's position for making bullet's starting point */  
void spawn_bullet(Player_t *player) {
    self_bullets[player->ypos] = player->xpos + 1;
}

/* The array state of bullet in local funkit and to send the state of outgoing bullet in the other funkit */
void move_self_bullets(void) {
    for (size_t i = BOARDHEIGHT + 1; i > 0; i--) {
        self_bullets[i] = self_bullets[i - 1];
        self_bullets[i - 1] = 0;
    }
    if (self_bullets[BOARDHEIGHT] > 0) {
        uint8_t outgoing_bullet = 0;
        // Mirror column of bullet to other funkit
        outgoing_bullet = 8 - (self_bullets[BOARDHEIGHT]);
        ir_uart_putc (outgoing_bullet);
    }
}

/** The array state of bullet in the other funkit that the local player shoot
    @param player To verify if the bullet reached player or not */  
void move_outgoing_bullets(Player_t *player) {
    for (size_t i = 0; i < BOARDHEIGHT - 1; i++) {
        outgoing_bullets[i] = outgoing_bullets[i + 1];
        outgoing_bullets[i + 1] = 0;
    }
    if (outgoing_bullets[player->ypos] == player->xpos + 1) {
        pio_output_high(LED1_PIO);
        outgoing_bullets[player->ypos] = 0;
        ir_uart_putc(WIN_SIGNAL);
        display_end_round(false);
    }
}

/* Receive the outgoing ir signals */
void ir_poll_signals(void) {
    if (ir_uart_read_ready_p ()) {
        uint8_t outgoing_signal = ir_uart_getc ();
        // If bullet then place on our dot matrix
        if (outgoing_signal < 8) {
            outgoing_bullets[4] = outgoing_signal;
        }
        // If win signal then display win
        if (outgoing_signal == WIN_SIGNAL) {
            display_end_round(true);
        }
    }
}

/* Display player's bullets in matrix */
void displays_bullets(void) {
    for (size_t i = 0; i < BOARDHEIGHT; i++) {
        display_entity(self_bullets[i] - 1, i);
        display_entity(outgoing_bullets[i] - 1, i);
    }
}
