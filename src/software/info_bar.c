 
char _time_buffer[30];

int32_t _time_sec = 0;
int32_t _time_minute = 0;
int32_t _time_hour = 0;
int32_t _time_frame = 0;
struct tm * _timeinfo = 0;

static void info_bar_initialize() {
   time_t rawtime;
   time(&rawtime);
   _timeinfo = localtime(&rawtime);

   _time_sec = _timeinfo->tm_sec;
   _time_minute = _timeinfo->tm_min;
   _time_hour = _timeinfo->tm_hour;

   snprintf(_time_buffer, 30, "%d:%d:%d", _time_hour, _time_minute, _time_sec);
}

static void info_bar_update() {
   _time_frame++;
   bool new_sec = false;

   if (_time_frame >= 30) {
      _time_sec++;
      new_sec = true;
      _time_frame = 0;
   }

   if (_time_sec >= 60) {
      _time_minute++;
      _time_sec = 0;
   }
   if (_time_minute >= 60) {
      _time_hour++;
      _time_minute = 0;
   }

   if (new_sec)
      snprintf(_time_buffer, 30, "%d:%d:%d", _time_hour, _time_minute, _time_sec);
}

static void info_bar_draw() {
   vga_adapter *adapter = vga_adapter_get_default();

   draw_rectangle(0, 0, adapter->screen_width, SOFTWARE_DRAW_Y_START, color_rgb(0,40,150));
   draw_text(2, 2, _time_buffer);
}

static void info_bar_destroy() {

}

software_interface _info_bar_software = {
   "Info bar",
   info_bar_initialize,
   info_bar_update,
   info_bar_draw,
   info_bar_destroy,
};