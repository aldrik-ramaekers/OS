#include "font8x8_basic.h"

void draw_pixel(vga_adapter* adapter, int32_t x, int32_t y, int32_t color)
{
   int32_t pixel_buf_ptr = (int32_t)adapter->back_buffer_address;

   if (x < 0) return;
   if (y < 0) return;
   if (x >= adapter->screen_width) return;
   if (y >= adapter->screen_height) return;

   x = x << 1;
   y = y << 10;

   int32_t pixel_ptr = pixel_buf_ptr + (y) + (x);
   *(int16_t*)pixel_ptr = color;
}

void draw_rectangle(vga_adapter* adapter, int32_t x, int32_t y, int32_t w, int32_t h, int32_t color)
{
   int32_t pixel_buf_ptr = (int32_t)adapter->back_buffer_address;

   if (x < 0) {
      w += x;
      x = 0;
   }

   if (y < 0) { 
      h += y;
      y = 0;
   }

   if (y > adapter->screen_height) return;
   if (x > adapter->screen_width) return;

   if (w <= 0) return;
   if (h <= 0) return;

   if (x + w >= adapter->screen_width) w -= (x + w) - adapter->screen_width;
   if (y + h >= adapter->screen_height) h -= (y + h) - adapter->screen_height;

   for (int32_t row = y; row < y+h; row++)
   {
      int32_t yy = (row<<10);

      for (int32_t col = x; col < x+w; col++)
      {
         int32_t pixel_ptr = pixel_buf_ptr + yy + (col<<1);
         *(int16_t*)pixel_ptr = color;
      }
   }
}

 __attribute__((flatten))
void draw_text(vga_adapter* adapter, int32_t x, int32_t y, char* text)
{
   x*=8;
   y*=8;

   int32_t offset = 0;
   while (*(text)) {
      char* c = font8x8_basic[(uint8_t)(*text)];

      if (x + offset > adapter->screen_width) {
         y += 8;
         offset = 0;
      }

      // @speed: stop using draw_pixel

      for (int8_t yy = 0; yy < 8; yy++) {
         for (int8_t xx = 0; xx < 8; xx++) {
            if ((c[yy] >> xx) & 0x1)
               draw_pixel(adapter, x+xx + offset, y+yy, 0xFFFFFFFF);
         }
      }
      
      offset += 8;
      ++text;
   }
   
}

void draw_clear_screen(vga_adapter* adapter) {
   memset(adapter->back_buffer_address, 0, 0x3FFFF);
}