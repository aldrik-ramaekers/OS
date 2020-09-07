#ifndef INCLUDE_VIDEO_VIDEO_H
#define INCLUDE_VIDEO_VIDEO_H

typedef struct t_vga_adapter
{
   int32_t* front_buffer_address;
   int32_t* back_buffer_address;
   int16_t width;
   int16_t height;
   int32_t status;
} vga_adapter __attribute__((packed));

vga_adapter* vga_adapter_initialize();
void vga_adapter_wait_for_vsync(vga_adapter* adapter);

#endif