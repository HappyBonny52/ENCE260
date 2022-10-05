#include "system.h"
#include "display.h"
#include "player.h"
#include "pacer.h"
#include "controls.h"
#include "navswitch.h"

int main (void)
{
    system_init ();
    pacer_init (300);
    display_init ();
    navswitch_init ();
    Player_t player = player_init(3, 4);
    uint8_t tick = 0;
    Action_e action = null;

    while (1)
    {
        pacer_wait();
        tick ++;
        if ((tick % 2) == 0) {
            display_player(&player);
        }
        if (tick >= 20) {
            action = navswitch_poll();
            handle_player(&player, action);
            action = null;
            tick = 0;
        }
    }
}
