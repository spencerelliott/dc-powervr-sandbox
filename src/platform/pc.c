#include <stdio.h>

#include "common.h"
#include "platform.h"

void preinit_platform() {

}

void init_platform() {
    printf("Hello from the PC version of %s!\n", PROJECT_NAME);
}

void cleanup_platform() {

}