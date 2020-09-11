
int8_t switch_is_on(int8_t index) {
   if (index < 0 || index > 9) return 0;

   int32_t val = *(int32_t*)SW_BASE;
   return (val >> index) & 0x1;
}