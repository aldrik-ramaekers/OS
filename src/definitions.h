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

#include "address_map_arm.h"

#include "video/vga.h"
#include "video/vga.c"