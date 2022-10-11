#include "system.h"
#include "pio.h"
#include "display_main.h"
#include "player.h"
#include "pacer.h"
#include "controls.h"
#include "navswitch.h"
#include "bullet.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15

int main (void)
{

    bool is_intro = true;
    bool is_finished = false; //when player got shot
    system_init ();
    /* Initialise tinygl. */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE); //MESSAGE_RATE : the speed of the displayed message
    /* Set the message using tinygl_text().  */
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text("SHOOT or DODGE!");

    pacer_init (500);


    display_main_init ();
    navswitch_init ();
    
    Player_t player = player_init(3, 0);
    uint8_t tick = 0;

    while (1)
    {
        pacer_wait();
        if (is_intro) {
            tinygl_update ();
            navswitch_update();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                /* Initialise the pins of the LED matrix.  */
                display_main_init();
                is_intro = false;
                tinygl_clear ();
            }
        }
        else {
            tinygl_update();
            tick ++;
            if ((tick % 2) == 0) {
                /* display_main_bullet(); */
                /* display_dot(player.xpos, player.ypos); */
                /* display_main_player(&player); */
                display_entity(player.xpos, player.ypos);
                display_main_bullets();
            }

            if ((tick % 2) == 1) {
                tinygl_clear();
            }

            if ((tick % 20) == 0) {
                Action_e action = navswitch_poll();
                handle_player(&player, action);
            }

            if (tick >= 50) {
                move_self_bullets();
                tick = 0;
            }

        }
        

        
    }
}
