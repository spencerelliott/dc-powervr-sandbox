#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef DREAMCAST
#include <kos.h>
#else
#include <stdio.h>
#endif

#ifdef DEBUG
    #define DEBUG_PRINT(m, ...) printf(m, __VA_ARGS__) // Prints debug information to the console
#else
    #define DEBUG_PRINT(m, ...) // Prints debug information to the console
#endif

#endif