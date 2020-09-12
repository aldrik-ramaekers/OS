typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
#if __WORDSIZE == 64
   typedef long int int64_t;
#else
   __extension__
   typedef long long int int64_t;
#endif

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
#if __WORDSIZE == 64
   typedef unsigned long int uint64_t;
#else
   __extension__
   typedef unsigned long long int uint64_t;
#endif

#define bool uint8_t
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "misc/address_map_arm.h"

// System
#include "software/interface/software_interface.h"
#include "software/software_registry.h"
#include "misc/string.h"
#include "allocator.h"
#include "hardware/vga.h"
#include "hardware/interrupts.h"
#include "hardware/pushbutton.h"
#include "hardware/switch.h"
#include "hardware/7seg_display.h"
#include "video/color.h"
#include "video/draw.h"
#include "console.h"

#include "misc/assert.h"
#include "misc/string.c"
#include "allocator.c"
#include "hardware/vga.c"
#include "hardware/interrupts.c"
#include "hardware/pushbutton.c"
#include "hardware/switch.c"
#include "hardware/7seg_display.c"
#include "video/color.c"
#include "video/draw.c"
#include "console.c"

// System software
#include "software/info_bar.c"

// Software
#include "software/pong.c"

#include "software/software_registry.c"