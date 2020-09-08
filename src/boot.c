#include "definitions.h"

/* function prototypes */
void video_text(int, int, char *);
void video_box(int, int, int, int, short, vga_adapter*);
int  resample_rgb(int, int);
int  get_data_bits(int);

#define STANDARD_X 320
#define STANDARD_Y 240

/* global variables */
int screen_x;
int screen_y;
int res_offset = 0;
int col_offset = 0;

/*******************************************************************************
 * This program demonstrates use of the video in the computer system.
 * Draws a blue box on the video display, and places a text string inside the
 * box
 ******************************************************************************/
int main(void) {

    color_initialize();
    vga_adapter* adapter = vga_adapter_initialize();

    // clear screen
    draw_rectangle(adapter, 0, 0, adapter->screen_width, adapter->screen_height, color_rgb(0,0,0));

    int32_t y = 0;
    int32_t x = 0;
    int xd = 1;
    int yd = 1;
    while (1)
    {
        draw_rectangle(adapter, x, y, 50, 50, color_rgb(0,0,0));

        x += xd;
        y += yd;

        draw_rectangle(adapter, x, y, 50, 50, color_rgb(255, 0, y));

        draw_text(adapter, 2, 2, "BAZINGA!\0");

        if (x >= adapter->screen_width-50) xd = -xd;
        if (y >= adapter->screen_height-50) yd = -yd;
        if (x <= 0) xd = -xd;
        if (y <= 0) yd = -yd;

        vga_adapter_wait_for_vsync(adapter);
    }

    return 0;
}