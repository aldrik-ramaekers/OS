static int8_t _press_state[4];

int8_t pushbutton_is_pressed(int8_t index)
{
   assert(index >= 0 && index < 4);

   int8_t pressed = _press_state[index];
   _press_state[index] = 0;

   return pressed;
}

void pushbutton_set_pressed(int8_t index)
{
   assert(index >= 0 && index < 4);

   _press_state[index] = 1;
}