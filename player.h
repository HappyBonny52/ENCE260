#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

typedef struct Player_t {
    int8_t xpos;
    int8_t ypos;
} Player_t;

void move_x_pos(int8_t direction, Player_t* player);

void move_y_pos(int8_t direction, Player_t* player);

#endif // !PLAYER_H
