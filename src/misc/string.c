int32_t string_length(char *source)
{
   int32_t str_len = 0; 
   char *tmp = source;
   while(*tmp) tmp++;
   
   str_len = tmp - source;
   return str_len;
}

void string_copy(char* destination, char *source)
{
   int32_t count = 0;
   while(*source)
   {
      destination[count++] = *source++;
   }
}