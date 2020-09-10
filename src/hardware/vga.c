
vga_adapter* vga_adapter_initialize() {
   color_initialize();

   vga_adapter* adapter = (vga_adapter*)PIXEL_BUF_CTRL_BASE;
   adapter->back_buffer_address = (int32_t*)0xC0000000; //(int32_t*)mem_alloc(0x3FFFF);

   _default_vga_adapter = adapter;

   draw_rectangle(adapter, 0, 0, adapter->screen_width, adapter->screen_height, color_rgb(0,0,0));

   return adapter;
}

vga_adapter* vga_adapter_get_default()
{
   if (!_default_vga_adapter) {
      vga_adapter_initialize();
   }

   return _default_vga_adapter;
}

void vga_adapter_wait_for_vsync(vga_adapter* adapter)
{
   adapter->front_buffer_address = (int32_t*)1;

   while(1)
   {
      volatile int8_t did_swap = adapter->status & 0x1;
      if (did_swap == 0) break;
   }
}