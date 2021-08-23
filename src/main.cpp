#include "debug.h"
#include "unim/unim.h"
#include "platform/platform.h"
#include "game/game.h"

#ifdef DREAMCAST
#define UNIM_PLATFORM PLATFORM_DREAMCAST
#else
#undef UNIM_PLATFORM
#define UNIM_PLATFORM PLATFORM_PC
#endif

#define PACK_COLOR32(r, g, b, a) (((a & 0xFF) << 24) | ((r << 16) & 0xFF) | ((g << 8) & 0xFF) | (b & 0xFF))

#ifdef DREAMCAST
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#endif

int main(int argc, char *argv[]) {
    Platform *platform = Platform::Get();
    Game game;

    game.SetPlatform(platform);

    platform->PreInit();

    Unim unim("", "");
    unim.PlayAnimation("Idle");

    platform->Init();
    game.Init();

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

    game.Cleanup();
    platform->Cleanup();

    return 0;  
}