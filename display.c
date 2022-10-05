#include "system.h"
#include "pio.h"
/* #include "pacer.h" */
#include <stdlib.h>

#include "display.h"


static const pio_t cols[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
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

    pio_output_low(cols[player->xpos]);
    pio_output_low(rows[player->ypos]);

    pio_output_high(cols[prev_col]);
    pio_output_high(rows[prev_row]);

    prev_col = player->xpos;
    prev_row = player->ypos;
}

