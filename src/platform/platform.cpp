#include "platform.h"

#ifndef DREAMCAST
#include "platform_pc.h"
#else
#include "platform_dc.h"
#endif

Platform* Platform::platform = nullptr;

Platform* const Platform::Get() {
    if (Platform::platform != nullptr) {
        return Platform::platform;
    }

    #ifndef DREAMCAST
    Platform::platform = new PcPlatform();
    #elif defined(DREAMCAST)
    Platform::platform = new DreamcastPlatform();
    #endif

    return Platform::platform;
}

Platform::Platform() : name("Generic") {

}

const char * const Platform::GetName() const {
    return this->name;
}