#include "renderer.h"

#ifndef DREAMCAST

#elif defined(DREAMCAST)
#include "renderer_dc.h"
#endif

Renderer* Renderer::renderer = nullptr;

Renderer* const Renderer::Get() {
    if (Renderer::renderer != nullptr) {
        return Renderer::renderer;
    }

    #ifndef DREAMCAST
    
    #elif defined(DREAMCAST)
    Renderer::renderer = new DreamcastRenderer();
    #endif

    return Renderer::renderer;
}