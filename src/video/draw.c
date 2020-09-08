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

   if (w <= 0) return;
   if (h <= 0) return;

   if (x + w >= adapter->screen_width) w -= (x + w) - adapter->screen_width;
   if (y + h >= adapter->screen_height) h -= (y + h) - adapter->screen_height;

   for (int32_t row = y; row < y+h; row++)
   {
      for (int32_t col = x; col < x+w; col++)
      {
         int32_t pixel_ptr = pixel_buf_ptr + (row<<10) + (col<<1);
         *(int16_t*)pixel_ptr = color;
      }
   }
}

void draw_text(vga_adapter* adapter, int32_t x, int32_t y, char* text)
{
   int32_t offset;
   volatile char* character_buffer = (char *)FPGA_CHAR_BASE;

   offset = (y << 7) + x;
   while (*(text)) {
      *(character_buffer + offset) = *(text); 
      ++text;
      ++offset;
    }
}