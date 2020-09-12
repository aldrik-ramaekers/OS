#ifndef INCLUDE_VIDEO_DRAW_H
#define INCLUDE_VIDEO_DRAW_H

#define SOFTWARE_DRAW_Y_START 12

void draw_pixel(int32_t x, int32_t y, int32_t color);
void draw_rectangle(int32_t x, int32_t y, int32_t w, int32_t h, int32_t color);
void draw_clear_screen();

void draw_text(int32_t x, int32_t y, char* text);

#endif