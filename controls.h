#ifndef CONTROLS_H
#define CONTROLS_H

#include "player.h"

typedef enum Action_e {
    null,
    left,
    down,
    right,
    up,
    attack,
} Action_e;

Action_e navswitch_poll(void);

void handle_player(Player_t *player, Action_e action);

#endif // !CONTROLS_H
