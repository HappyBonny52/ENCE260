#include "tinygl.h"
#include <stdlib.h>
#include "system.h"
#include "pio.h"
#include "display_main.h"
#include "navswitch.h"
#include "pacer.h"

/* Useful arrays for mapping columns and rows on pio
 * NOTE: Columns and rows are swapped from the datasheet model
 * as the game is designed for the funkit to be played sideways. */
static const pio_t cols[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/* The 'rows' here are also in reverse order such that the row closest
 * to the nav switch is considered 0 while the furthest row is considered 5. */
static const pio_t rows[] =
{
    LEDMAT_COL5_PIO, LEDMAT_COL4_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL2_PIO, LEDMAT_COL1_PIO
};

void display_main_init(void) {
    for (size_t i = 0; i < LEDMAT_COLS_NUM; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }

    for (size_t i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
}

void display_entity(int8_t x, int8_t y) {
    tinygl_point_t point = {.x = (BOARDHEIGHT - 1 - y), .y = x};
    tinygl_draw_point(point, 1);
}

void display_intro(void) {
    bool is_intro = true;
    /* Set the message using tinygl_text().  */
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
    tinygl_text("SHOOT OR DODGE!");
    while (is_intro) {
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
    }
}

void display_state(void) {
    /* Set the message using tinygl_text().  */
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
    tinygl_text("!HIT!");
    bool is_player_hit =true;
    while (is_player_hit) {
        pacer_wait();
        if (is_player_hit) {
            tinygl_update ();
            navswitch_update();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                /* Initialise the pins of the LED matrix.  */
                display_main_init();
                is_player_hit = false;
                tinygl_clear ();
            }
        }
    }
}

void display_result(void) {
    /* Set the message using tinygl_text().  */
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(1);
    tinygl_text("GOOD");
    bool is_finished =true;
    while (is_finished) {
        pacer_wait();
        if (is_finished) {
            tinygl_update ();
            navswitch_update();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                /* Initialise the pins of the LED matrix.  */
                display_main_init();
                is_finished = false;
                tinygl_clear ();
            }
        }
    }
}