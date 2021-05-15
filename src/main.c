#define PROJECT_NAME "PVR Test"

#include <kos.h>
#include <dc/pvr.h>

// kosext2fs
#include <ext2/fs_ext2.h>

// kosutils
#include <kos/bspline.h>
#include <kos/img.h>
#include <kos/md5.h>
#include <kos/netcfg.h>
#include <kos/pcx.h>
#include <kos/vector.h>

int main(int argc, char *argv[]) {
    pvr_init_defaults();
    pvr_set_bg_color(1.0f, 0.0f, 0.0f);
    
    while(1) {
        vram_s[0] = 0x1FF << 5;
        vram_s[1] = 0x1FF << 5;
        vram_s[2] = 255;
        vram_s[3] = 255;
        vram_s[4] = 255;

        printf("Hello\n");


        pvr_wait_ready();
        pvr_scene_begin();

        pvr_scene_finish();
    }
    
}