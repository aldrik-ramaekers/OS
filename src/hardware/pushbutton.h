#ifndef INCLUDE_HARDWARE_PUSHBUTTON_H
#define INCLUDE_HARDWARE_PUSHBUTTON_H

// Valid index: 0-3
int8_t pushbutton_is_pressed(int8_t index);
void pushbutton_set_pressed(int8_t index); 

#endif