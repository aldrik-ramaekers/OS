
static int8_t get_bits_per_pixel(int32_t mode) {
    switch (mode) {
    case 0x0:
        return 1;
    case 0x7:
        return 8;
    case 0x11:
        return 8;
    case 0x12:
        return 9;
    case 0x14:
        return 16;
    case 0x17:
        return 24;
    case 0x19:
        return 30;
    case 0x31:
        return 8;
    case 0x32:
        return 12;
    case 0x33:
        return 16;
    case 0x37:
        return 32;
    case 0x39:
        return 40;
    }

    assert(0);
    return 0;
}

void color_initialize()
{
   volatile int* rgb_status = (int *)(RGB_RESAMPLER_BASE);
   int8_t bits = get_bits_per_pixel(*rgb_status & 0x3F);

   _pits_per_pixel = bits;
}

int32_t color_rgb(int32_t r, int32_t g, int32_t b)
{
   int32_t color = (r << 16) | (g << 8) | (b << 0);

   if (_pits_per_pixel == 8) {
      color = (((color >> 16) & 0x000000E0) | ((color >> 11) & 0x0000001C) | ((color >> 6) & 0x00000003));
      color = (color << 8) | color;
   } else if (_pits_per_pixel == 16) {
      color = (((color >> 8) & 0x0000F800) | ((color >> 5) & 0x000007E0) | ((color >> 3) & 0x0000001F));
   }
   else
   {
      assert(0);
   }
   
   return color;
}