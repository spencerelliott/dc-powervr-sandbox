#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <kos.h>

#ifdef DEBUG
    #define DEBUG_PRINT(m, ...) printf(m, __VA_ARGS__) // Prints debug information to the console
#else
    #define DEBUG_PRINT(m, ...) // Prints debug information to the console
#endif

#endif