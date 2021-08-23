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

#include "common.h"
#include "platform.h"

void preinit_platform() {
    #ifdef DEBUG
    gdb_init();
    printf("GDB connection established!\n");
    #endif
}

void init_platform() {
    pvr_init_defaults();
    pvr_set_bg_color(1.0f, 0.0f, 0.0f);
}

void cleanup_platform() {

}