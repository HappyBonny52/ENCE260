#include <stdio.h>
#include <stdint.h>
#include "player.h"

Player_t player_init (int8_t xpos, int8_t ypos) {
    return (Player_t) {.xpos = xpos, .ypos = ypos};
}

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

