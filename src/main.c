#include "debug.h"
#include "unim/unim.h"
#include "platform/platform.h"

#ifdef DREAMCAST
#define UNIM_PLATFORM PLATFORM_DREAMCAST
#else
#define UNIM_PLATFORM PLATFORM_PC
#endif

#define PACK_COLOR32(r, g, b, a) (((a & 0xFF) << 24) | ((r << 16) & 0xFF) | ((g << 8) & 0xFF) | (b & 0xFF))

#ifdef DREAMCAST
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#endif

int main(int argc, char *argv[]) {
    preinit_platform();

    unim_t unim;

    unim_init(&unim, "UnimMech.bytes", "UnimMech.png");
    unim_play_animation(&unim, "Idle");

    init_platform();

    #ifdef DREAMCAST
    while(1) {
        vram_s[0] = 0x1FF << 5;
        vram_s[1] = 0x1FF << 5;
        vram_s[2] = 255;
        vram_s[3] = 255;
        vram_s[4] = 255;

        pvr_wait_ready();
        pvr_scene_begin();

        pvr_list_begin(PVR_LIST_OP_POLY);

        pvr_vertex_t vert;
        vert.flags = PVR_CMD_VERTEX;
        vert.argb = PACK_COLOR32(255, 0, 0, 255);

        vert.x = 0.5f;
        vert.y = 0.5f;
        
        

        pvr_list_finish();

        pvr_scene_finish();
    }
    #endif

    cleanup_platform();

    return 0;  
}