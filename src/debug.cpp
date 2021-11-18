#include "debug.h"

void Abort(const char* message, ...) {
    #ifdef ENGINE_DEBUG
    va_list args;

    printf("---------- ABORT ----------\n\nMessage: ");
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
    printf("\n\nPlease shutdown the game and retry.\n");
    printf("---------------------------\n");

    // Loop here forever so we do not continue
    while(1) { }
    #endif
}