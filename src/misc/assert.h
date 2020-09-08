#define assert(_s_) { if (!(_s_)) { assert_failed(__FILE__, __LINE__); } }

void assert_failed(char* file, int32_t line)
{
   vga_adapter* adapter = vga_adapter_get_default();
   
   char buffer[1024];
   snprintf(buffer, 1024, "Assertion failed at // %s:%d", file, line);

   draw_rectangle(adapter, 0, 0, adapter->screen_width, adapter->screen_height, color_rgb(0,0,0));
   draw_text(adapter, 0, 1, buffer);
   vga_adapter_wait_for_vsync(adapter);

   abort();
}

