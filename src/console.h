#ifndef INCLUDE_CONSOLE_H
#define INCLUDE_CONSOLE_H

typedef struct t_console
{
   int32_t history_count;
   char** history;
   char* current_line;
} console;

void console_report_message(char *message);
void console_draw();

#endif