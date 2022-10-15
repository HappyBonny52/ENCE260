/** @file   display_main.c
    @author Aaron Sevilla, Bonghyun Kwon
    @date   15 October 2022
    @brief  Displaying game state
*/
#include <stdlib.h>
#include <string.h>
#include "tinygl.h"
#include "system.h"
#include "pio.h"
#include "display_main.h"
#include "navswitch.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define MESSAGE_RATE 30

/* For storing player's score */
static uint8_t games_won = 0;
static uint8_t games_lost = 0;


/* Useful arrays for mapping columns and rows on pio
 * NOTE: Columns and rows are swapped from the datasheet model
 * as the game is designed for the funkit to be played sideways. */
/* static const pio_t cols[] = */
/* { */
/*     LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,  */
/*     LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO, */
/*     LEDMAT_ROW7_PIO */
/* }; */

/* The 'rows' here are also in reverse order such that the row closest
 * to the nav switch is considered 0 while the furthest row is considered 5. */
/* static const pio_t rows[] = */
/* { */
/*     LEDMAT_COL5_PIO, LEDMAT_COL4_PIO, LEDMAT_COL3_PIO, */
/*     LEDMAT_COL2_PIO, LEDMAT_COL1_PIO */
/* }; */

/* Initialise tinygl and display. */
void display_main_init(void) {
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE); //MESSAGE_RATE : the speed of the displayed message
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
}

void display_entity(int8_t x, int8_t y) {
    tinygl_point_t point = {.x = (BOARDHEIGHT - 1 - y), .y = x};
    tinygl_draw_point(point, 1);
}

/* Display the start of the game */
void display_intro(void) {
    /* Set the message using tinygl_text().  */
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
    tinygl_text("SHOOT OR DODGE!");
    while (true) {
        pacer_wait();
        tinygl_update ();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            /* Initialise the pins of the LED matrix.  */
            /* display_main_init(); */
            tinygl_clear ();
            return;
        }
    }
}

/* Display the state of the game in each round*/
static void display_state(void) {
    char message[4] = {games_won + '0', '-', games_lost + '0', '\0'};
    tinygl_text(message);
    /* tinygl_text("OOPS!"); */
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
            /* Initialise the pins of the LED matrix.  */
            /* display_main_init(); */
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


void poll_winner(void) {
    if (ir_uart_read_ready_p ()) {
        uint8_t winstate = ir_uart_getc ();
        if (winstate == '!') {
            display_end_round(true);
        }
    }

}
