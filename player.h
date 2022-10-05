#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#define BOARDWIDTH 6
#define BOARDHEIGHT 4

typedef struct Player_t {
    int8_t xpos;
    int8_t ypos;
} Player_t;

Player_t player_init (int8_t xpos, int8_t ypos);

void move_x_pos(int8_t direction, Player_t* player);

void move_y_pos(int8_t direction, Player_t* player);

#endif // !PLAYER_H
