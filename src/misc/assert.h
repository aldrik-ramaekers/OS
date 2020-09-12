#define assert(_s_) { if (!(_s_)) { assert_failed(__FILE__, __LINE__); } }

void assert_failed(char* file, int32_t line)
{
   vga_adapter* adapter = vga_adapter_get_default();
   
   char buffer[1024];
   snprintf(buffer, 1024, "Assertion failed at // %s:%d", file, line);

   draw_clear_screen(adapter);
   draw_text(0, 1, buffer);
   vga_adapter_wait_for_vsync(adapter);

   while(1);
}

