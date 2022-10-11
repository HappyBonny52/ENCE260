#include <stdint.h>
#include <stdlib.h>
#include "bullet.h"
#include "display_main.h"

// Array of bullets where values are x axes and index is y axes
static uint8_t self_bullets[BOARDHEIGHT + 1] = {0};

void spawn_bullet(Player_t *player) {
    self_bullets[player->ypos] = player->xpos + 1;
}

void move_self_bullets(void) {
    for (size_t i = BOARDHEIGHT + 1; i > 0; i--) {
        self_bullets[i] = self_bullets[i - 1];
        self_bullets[i - 1] = 0;
    }
}

void display_main_bullet(void) {
    for (size_t i = 0; i < BOARDHEIGHT; i++) {
        if (self_bullets[i] > 0) {
            display_entity(i, self_bullets[i] - 1);
        }
    }
    /* if (self_bullets[BOARDHEIGHT] > 0) { */
    /*     pass; */
    /* } */
}
