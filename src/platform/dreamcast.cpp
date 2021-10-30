#include "common.h"
#include "platform.h"
#include "dreamcast.h"

DreamcastPlatform::DreamcastPlatform() {
    this->name = "Dreamcast";
}

void DreamcastPlatform::PreInit() {
    
}

void DreamcastPlatform::Init() {

}

bool DreamcastPlatform::ProcessFrame() {
    return false;
}

void DreamcastPlatform::Cleanup() {

}