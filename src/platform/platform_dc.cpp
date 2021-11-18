#include "common.h"
#include "platform.h"
#include "platform_dc.h"

DreamcastPlatform::DreamcastPlatform() {
    this->name = "Dreamcast";
}

void DreamcastPlatform::Init() {

}

bool DreamcastPlatform::ProcessFrame() {
    return false;
}

void DreamcastPlatform::Cleanup() {

}