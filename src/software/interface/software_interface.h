#ifndef INCLUDE_SOFTWARE_INTERFACE_SOFTWARE_INTERFACE_H
#define INCLUDE_SOFTWARE_INTERFACE_SOFTWARE_INTERFACE_H

typedef struct t_software_interface
{
   char* name;
   void (*initialize)(void);
   void (*update)(void);
   void (*draw)(void);
   void (*destroy)(void);
} software_interface;

#endif