/** @file   game.c
    @author Aaron Sevilla, ase89
    @author Bonghyun Kwon, bkw31
    @date   17 October 2022
    @brief  A simple shooting game for 2 players
*/
#include "system.h"
#include "pio.h"
#include "displays.h"
#include "player.h"
#include "pacer.h"
#include "navswitch.h"
#include "bullet.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30
#define NAVIGATION_RATE 20
#define BULLET_RATE 40
#define START_X_POS 3
#define START_Y_POS 0

/* Main game loop for 'SHOOT and DOGDGE' */
int main (void)
{
    /* Initialize display, buttons, Ir_uart, etc.*/
    system_init ();
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
    pacer_init (PACER_RATE);
    displays_init ();
    navswitch_init ();
    ir_uart_init ();

    Player_t player = player_init(START_X_POS, START_Y_POS);
    uint8_t tick = 0;
    display_intro();

    /* Playing games and showing each state will be repeated 
    *  until all the matches completed */
    while (1)
    {
        pacer_wait();
        pio_output_low(LED1_PIO);
        tick ++;
        ir_poll_signals();

        if (tick % 2 == 0) {
            display_entity(player.xpos, player.ypos);
            displays_bullets();
        } else {
            tinygl_clear();
        }
        tinygl_update();

        if ((tick % NAVIGATION_RATE) == 0) {
            Action_e action = navswitch_poll();
            handle_player(&player, action);
        }

        if (tick >= BULLET_RATE) {
            move_self_bullets();
            move_outgoing_bullets(&player);
            tick = 0;
        }
    }
}
