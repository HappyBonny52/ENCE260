#include "system.h"
#include "display.h"
#include "player.h"
#include "pacer.h"

int main (void)
{
    system_init ();
    pacer_init (200);
    display_init ();
    Player_t player = player_init(2, 0);
    uint8_t tick = 0;

    while (1)
    {
        pacer_wait();
        display_player(&player);
        tick ++;
        if (tick >= 50) {
            move_x_pos(1, &player);
            tick = 0;
        }
    }
}
