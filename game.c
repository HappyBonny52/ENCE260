/** @file   game.c
    @author Aaron Sevilla, Bonghyun Kwon
    @date   14 October 2022
    @brief  
*/
#include "system.h"
#include "pio.h"
#include "display_main.h"
#include "player.h"
#include "pacer.h"
#include "controls.h"
#include "navswitch.h"
#include "bullet.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30



int main (void)
{
    system_init ();
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
    pacer_init (PACER_RATE);
    display_main_init ();
    navswitch_init ();
    ir_uart_init ();

    Player_t player = player_init(3, 0);
    uint8_t tick = 0;
    display_intro();

    while (1)
    {
        pacer_wait();
        pio_output_low(LED1_PIO);
        tick ++;
        

        if (tick % 2 == 0) {
            display_entity(player.xpos, player.ypos);
            display_main_bullets();
            poll_winner();
        } else {
            ir_poll_bullets();
            tinygl_clear();
        }
        tinygl_update();

        if ((tick % 20) == 0) {
            Action_e action = navswitch_poll();
            handle_player(&player, action);
        }

        if (tick >= 40) {
            move_self_bullets();
            move_outgoing_bullets(&player);
            tick = 0;
        }
    }
}
