
void seg_display_set_value(int8_t value, int8_t index) {
   if (index < 0 || index > 5) return;
   if (value < -1 || value > 9) return;

   int8_t bit_offset = index * 8;
   int32_t *base = (int32_t*)HEX3_HEX0_BASE;

   if (index > 3) { 
      base = (int32_t*)HEX5_HEX4_BASE;
      bit_offset = (index - 4) * 8;
   }

   // int16_t least_significant = value % 10;
   // int16_t most_significant = value / 10;

   // reset value
   int32_t current_val = *base;
   current_val &= ~(0x0000007F << bit_offset);
   *base = current_val;

   if (value != -1) {
      uint32_t val = _seg_display_values[value];
      *base |= (val << bit_offset);
   }
}