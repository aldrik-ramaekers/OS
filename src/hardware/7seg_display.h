#ifndef INCLUDE_HARDWARE_7SEG_DISPLAY_H
#define INCLUDE_HARDWARE_7SEG_DISPLAY_H

#define SEG_DISPLAY_RESET 0x0

uint8_t _seg_display_values[] = {
   0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Value range: 0-9 or -1 to reset, index range: 0-5
void seg_display_set_value(int8_t value, int8_t index);

#endif