#include <dc/pvr.h>

#include "debug.h"
#include "renderer_dc.h"

void DreamcastRenderer::Init() {
    pvr_init_params_t init_params = {
        .opb_sizes = { PVR_BINSIZE_8, PVR_BINSIZE_0, PVR_BINSIZE_0, PVR_BINSIZE_8},
        .vertex_buf_size = 512 * 1024
    };

    if (pvr_init(&init_params)) {
        #ifdef ENGINE_DEBUG
        Abort("Could not initialize PVR!");
        #endif
    }

    pvr_set_bg_color(0.1f, 0.1f, 0.1f);
}

void DreamcastRenderer::Resize(unsigned int width, unsigned int height) {
    // We can't resize so do nothing
}

void DreamcastRenderer::DrawSprite() {

}