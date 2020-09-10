#ifndef INCLUDE_VIDEO_DRAW_H
#define INCLUDE_VIDEO_DRAW_H

void draw_pixel(vga_adapter* adapter, int32_t x, int32_t y, int32_t color);
void draw_rectangle(vga_adapter* adapter, int32_t x, int32_t y, int32_t w, int32_t h, int32_t color);
void draw_clear_screen(vga_adapter* adapter);

void draw_text(vga_adapter* adapter, int32_t x, int32_t y, char* text);

#endif