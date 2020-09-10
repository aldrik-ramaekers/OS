console _default_console = {0};

void console_report_message(char *message)
{
   _default_console.history_count++;
   
   if (_default_console.history == 0) {
      _default_console.history = mem_alloc(sizeof(char*) * _default_console.history_count);
   }
   else {
      _default_console.history = mem_realloc(_default_console.history, sizeof(char*) * _default_console.history_count);
   }

   int32_t str_len = string_length(message);

   char* new_message = mem_alloc(str_len+1);
   string_copy(new_message, message);
   new_message[str_len] = 0;

   _default_console.history[_default_console.history_count-1] = new_message;
}

void console_draw()
{
   int offset = 0;

   if (_default_console.history_count >= 60)
   {
      offset = _default_console.history_count - 60;
   }

   for (int i = offset; i < _default_console.history_count; i++)
   {
      draw_text(vga_adapter_get_default(), 0, i - offset, _default_console.history[i]);
   }
}