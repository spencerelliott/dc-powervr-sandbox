#include <stdio.h>

#include "common.h"
#include "platform.h"
#include "pc.h"

PcPlatform::PcPlatform() {
    this->name = "PC";
}

void PcPlatform::PreInit() {
    printf("Hello from %s!\n", PROJECT_NAME);
}

void PcPlatform::Init() {
    // Create a GLFW window
}

bool PcPlatform::ProcessFrame() {
    // Check the current input in the window
    return false;
}

void PcPlatform::Cleanup() {

}