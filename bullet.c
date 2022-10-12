#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bullet.h"
#include "display_main.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "system.h"
#include "pio.h"

// Array of bullets where values are x axes and index is y axes
static uint8_t self_bullets[BOARDHEIGHT + 1] = {0};
static uint8_t outgoing_bullets[BOARDHEIGHT + 1] = {0};

uint8_t outgoing_bullet = 0;

void spawn_bullet(Player_t *player) {
    self_bullets[player->ypos] = player->xpos + 1;
}


void move_self_bullets(void) {
    for (size_t i = BOARDHEIGHT + 1; i > 0; i--) {
        self_bullets[i] = self_bullets[i - 1];
        self_bullets[i - 1] = 0;
    }
    if (self_bullets[BOARDHEIGHT] > 0) {
        outgoing_bullet = 8-(self_bullets[BOARDHEIGHT]);
        ir_uart_putc (outgoing_bullet);
    }
}

void move_outgoing_bullets(Player_t *player) {
    for (size_t i = 0; i < BOARDHEIGHT - 1; i++) {
        outgoing_bullets[i] = outgoing_bullets[i + 1];
        outgoing_bullets[i + 1] = 0;      
    }
    if (outgoing_bullets[player->ypos] == player->xpos + 1) {
        pio_output_high(LED1_PIO);
        outgoing_bullets[player->ypos] = 0;
    }
}
void ir_poll(void) {
    if (ir_uart_read_ready_p ()) {
        outgoing_bullet = ir_uart_getc ();
        outgoing_bullets[4] = outgoing_bullet;
    }

}
void display_main_bullets(void) {
    for (size_t i = 0; i < BOARDHEIGHT; i++) {
        display_entity(self_bullets[i] - 1, i);
        display_entity(outgoing_bullets[i] - 1, i);
    }

}
