/** @file   displays.c
    @author Aaron Sevilla, ase89
    @author Bonghyun Kwon, bkw31
    @date   15 October 2022
    @brief  Displaying game states
*/
#include <stdlib.h>
#include <string.h>
#include "tinygl.h"
#include "system.h"
#include "pio.h"
#include "displays.h"
#include "navswitch.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"


/* For storing player's score */
static uint8_t games_won = 0;
static uint8_t games_lost = 0;


/* Initialise tinygl and display. */
void displays_init(void) {
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE); //MESSAGE_RATE : the speed of the displayed message
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
}


/* Display a dot used for player, self bullet, outgoing bullets */
void display_entity(int8_t x, int8_t y) {
    tinygl_point_t point = {.x = (BOARDHEIGHT - 1 - y), .y = x};
    tinygl_draw_point(point, 1);
}

/* Display the start of the game */
void display_intro(void) {
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
    tinygl_text("SHOOT & DODGE!");
    while (true) {
        pacer_wait();
        tinygl_update ();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            tinygl_clear ();
            return;
        }
    }
}

/* Display the state of the game in each round*/
static void display_state(void) {
    char message[4] = {games_won + '0', '-', games_lost + '0', '\0'};
    tinygl_text(message);
    while (true) {
        pacer_wait();
        tinygl_update ();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            tinygl_clear ();
            return;
        }
    }
}

/* Display the result of the game */
static void display_result(void) {
    /* Set the message using tinygl_text().  */
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
    if (games_won == 3) {
        tinygl_text(" WINNER!! ");
    } else {
        tinygl_text(" LOSER!! ");
    }
    games_won = 0;
    games_lost = 0;
    while (true) {
        pacer_wait();
        tinygl_update ();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            tinygl_clear ();
            return;
        }
    }
}

/* Collecting score in order to identify proper display of each state */
// NOTE: display_result and display_state are only called within this function
// and nowhere else in the project so they should be private
void display_end_round(bool win) {
    if (win) {
        games_won++;
    }
    else {
        games_lost++;
    }
    if (games_won == 3 || games_lost == 3){
        display_result();
    } else {
        display_state();
    }
}