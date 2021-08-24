#include "platform.h"

#ifndef DREAMCAST
#include "pc.h"
#else
#include "dreamcast.h"
#endif

Platform* Platform::platform = nullptr;

Platform* const Platform::Get() {
    if (Platform::platform != nullptr) {
        return Platform::platform;
    }

    #ifndef DREAMCAST
    Platform::platform = new PcPlatform();
    #else

    #endif

    return Platform::platform;
}

Platform::Platform() : name("Generic") {

}

const char * const Platform::GetName() const {
    return this->name;
}