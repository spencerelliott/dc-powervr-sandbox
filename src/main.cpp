#include "debug.h"
#include "platform/platform.h"
#include "game/game.h"
#include "renderer/renderer.h"


#define PACK_COLOR32(r, g, b, a) (((a & 0xFF) << 24) | ((r << 16) & 0xFF) | ((g << 8) & 0xFF) | (b & 0xFF))

#ifdef DREAMCAST
#include <kos.h>

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
#endif

int main(int argc, char *argv[]) {
    Platform *platform = Platform::Get();

    if (platform) {
        printf("Platform: %s\n", platform->GetName());
    }

    Game game;

    game.SetPlatform(platform);

    platform->Init();
    game.Init();


    while(game.IsRunning()) {
        bool shouldRun = platform->ProcessFrame();

        // If the platform needs to exit right away, do it here
        if (!shouldRun) {
            break;
        }

        game.Update();
    }

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