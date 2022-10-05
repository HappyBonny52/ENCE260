#include <stdio.h>
#include <stdint.h>
#include "playfield.h"

typedef struct Player_t {
    int8_t xpos;
    int8_t ypos;
} Player_t;

void move_x_pos(int8_t direction, Player_t* player) {
    if (direction == 1) {
        player->xpos++;
    }
    if (direction == -1) {
        player->xpos--;
    }
    if (player->xpos > BOARDWIDTH) {
        player->xpos = 0;
    }
    if (player->xpos < 0) {
        player->xpos = BOARDWIDTH;
    }
}

void move_y_pos(int8_t direction, Player_t* player) {
    if (direction == 1) {
        player->ypos++;
    }
    if (direction == -1) {
        player->ypos--;
    }
    if (player->ypos > BOARDHEIGHT) {
        player->ypos = 0;
    }
    if (player->ypos < 0) {
        player->ypos = BOARDHEIGHT;
    }
}
int main(void) {
    Player_t player = {.xpos = 0, .ypos = 0};
    printf("%i\n", player.xpos);
    move_x_pos(1, &player);
    printf("%i\n", player.xpos);
}
