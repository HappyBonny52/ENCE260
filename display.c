#include "system.h"
#include "pio.h"
/* #include "pacer.h" */
#include <stdlib.h>

#include "display.h"

/* Useful arrays for mapping columns and rows on pio
 * NOTE: Columns and rows are swapped from the datasheet model
 * as the game is designed for the funkit to be played sideways */
static const pio_t cols[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const pio_t rows[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

void display_init(void) {
    for (size_t i = 0; i < LEDMAT_COLS_NUM; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }

    for (size_t i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
}

void display_player(Player_t* player) {
    static uint8_t prev_col = 0;
    static uint8_t prev_row = 0;

    // Light up new player position
    pio_output_low(cols[player->xpos]);
    pio_output_low(rows[player->ypos]);

    if (prev_col == player->xpos && prev_row == player->ypos) {
        return;
    }
    // Dim old player position
    pio_output_high(cols[prev_col]);
    pio_output_high(rows[prev_row]);

    // Record previous position
    prev_col = player->xpos;
    prev_row = player->ypos;
}

