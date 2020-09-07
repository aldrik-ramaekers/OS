
vga_adapter* vga_adapter_initialize() {
   vga_adapter* adapter = (vga_adapter*)PIXEL_BUF_CTRL_BASE;
   adapter->back_buffer_address = (int*)0xC0000000;

   return adapter;
}

void vga_adapter_wait_for_vsync(vga_adapter* adapter)
{
   adapter->front_buffer_address = 1;

   while(1)
   {
      volatile int8_t did_swap = adapter->status & 0x1;
      if (did_swap == 0) break;
   }
}