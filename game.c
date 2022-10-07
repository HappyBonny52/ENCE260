#include "system.h"
#include "display_main.h"
#include "player.h"
#include "pacer.h"
#include "controls.h"
#include "navswitch.h"
#include "bullet.h"

int main (void)
{
    system_init ();
    pacer_init (500);
    display_init ();
    navswitch_init ();
    Player_t player = player_init(3, 0);
    uint8_t tick = 0;

    while (1)
    {
        pacer_wait();
        tick ++;
        if ((tick % 4) == 0) {
            display_bullet();
            /* display_dot(player.xpos, player.ypos); */
            display_player(&player);
        }
        if ((tick % 20) == 0) {
            Action_e action = navswitch_poll();
            handle_player(&player, action);
        }

        if (tick >= 100) {
            move_self_bullets();
            tick = 0;
        }
    }
}
