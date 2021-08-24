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

}

void PcPlatform::Cleanup() {

}