#include <stdint.h>
#include <stdlib.h>
#include "bullet.h"
#include "display_main.h"

// Array of bullets where values are x axes and index is y axes
static uint8_t self_bullets[BOARDHEIGHT + 1] = {0};
uint8_t outgoing_bullet = 0;

void spawn_bullet(Player_t *player) {
    self_bullets[player->ypos] = player->xpos + 1;
}

void move_self_bullets(void) {
    for (size_t i = BOARDHEIGHT + 1; i > 0; i--) {
        self_bullets[i] = self_bullets[i - 1];
        self_bullets[i - 1] = 0;
    }
    if (self_bullets[BOARDHEIGHT + 1] > 0) {
        outgoing_bullet = 8-(self_bullets[BOARDHEIGHT + 1]);
        ir_uart_putc (outgoing_bullet);
    }
}

void display_main_bullets(void) {
    for (size_t i = 0; i < BOARDHEIGHT; i++) {
        display_entity(self_bullets[i] - 1, i);
    }
}
