#include "platform.h"

Platform* Platform::platform = nullptr;

Platform* Platform::Get() {
    if (Platform::platform != nullptr) {
        return Platform::platform;
    }
    return nullptr;
}