#ifndef INCLUDE_VIDEO_COLOR_H
#define INCLUDE_VIDEO_COLOR_H

static int8_t _pits_per_pixel = 16;

void color_initialize();
int32_t color_rgb(int32_t r, int32_t g, int32_t b);

#endif