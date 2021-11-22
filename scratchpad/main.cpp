/* KallistiOS ##version##
   examples/dreamcast/pvr/bumpmap/bump.c
   Copyright (C) 2014 Lawrence Sebald
   This example demonstrates the use of bumpmaps on a surface.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <dc/pvr.h>
#include <dc/maple.h>
#include <dc/fmath.h>
#include <dc/maple/controller.h>

#include <kmg/kmg.h>

#include <kos.h>
#include <math.h>

static pvr_vertex_t verts[2 * 4];

static pvr_poly_hdr_t phdr[2];
static float bumpiness = 0.5f;
static pvr_ptr_t bump, txr, light;
static int textured = 1;

static float mx = 290.0f, my = 290.0f;

int counter = 0;

static pvr_mod_hdr_t mhdr, mhdr2;

#define SIZE 256

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

#define CLAMP(low, high, value) (value < low ? low : (value > high ? high : value))

typedef struct Vector2 {
    float x;
    float y;
} Vector2_t;

static Vector2_t light_pos;

float angle_between(Vector2_t* v1, Vector2_t* v2) {
    return atan2f(v2->y - v1->y, v2->x - v1->x);
}

float distance_from(Vector2_t* from, Vector2_t* to) {
    float dx = to->x - from->x;
    float dy = to->y - from->y;

    return abs(sqrtf(dx*dx + dy*dy));
}

static pvr_ptr_t load_texture(const char fn[]) {
    FILE *fp;
    pvr_ptr_t rv;

    if(!(rv = pvr_mem_malloc(SIZE * SIZE * 2))) {
        printf("Failed to allocate PVR memory!\n");
        return NULL;
    }

    if(!(fp = fopen(fn, "rb"))) {
        printf("Couldn't open file: %s\n", strerror(errno));
        pvr_mem_free(rv);
        return NULL;
    }

    if(fread(rv, 1, SIZE * SIZE * 2, fp) != SIZE * SIZE * 2) {
        printf("Failed to read texture from file!\n");
        fclose(fp);
        pvr_mem_free(rv);
        return NULL;
    }
    
    fclose(fp);

    return rv;
}

static pvr_ptr_t load_kmg(const char fn[]) {
    kos_img_t img;
    pvr_ptr_t rv;

    if(kmg_to_img(fn, &img)) {
        printf("Failed to load image file: %s\n", fn);
        return NULL;
    }

    if(!(rv = pvr_mem_malloc(img.byte_count))) {
        printf("Couldn't allocate memory for texture!\n");
        kos_img_free(&img, 0);
        return NULL;
    }

    pvr_txr_load_kimg(&img, rv, 0);
    kos_img_free(&img, 0);

    return rv;
}

static void setup() {
    int i = 0;
    pvr_poly_cxt_t cxt;

    /* Load the textures. */
    if(!(bump = load_texture("/rd/bumpmap.raw")))
        exit(EXIT_FAILURE);

    if(!(txr = load_kmg("/rd/bricks.kmg"))) {
        pvr_mem_free(bump);
        exit(EXIT_FAILURE);
    }

    if(!(light = load_kmg("/rd/light.kmg"))) {
        pvr_mem_free(bump);
        exit(EXIT_FAILURE);
    }

    /* Fill in the sprite context for the bumpmap itself. This is not for the
       polygon that will actually appear bumped. */
    // pvr_poly_cxt_txr_mod(&cxt, PVR_LIST_OP_POLY,
    //                    PVR_TXRFMT_BUMP | PVR_TXRFMT_TWIDDLED, 256, 256, bump,
    //                    PVR_FILTER_NONE, PVR_TXRFMT_ARGB4444 | PVR_TXRFMT_TWIDDLED | PVR_TXRFMT_VQ_ENABLE, 256, 256,
    //                    light, PVR_FILTER_NONE);
    // cxt.gen.specular = PVR_SPECULAR_ENABLE;
    // cxt.txr.env = PVR_TXRENV_DECAL;
    // pvr_poly_mod_compile(&phdr[0], &cxt);

    /* Fill in the sprite context for the polygon to be "bumped" by the map. */
    pvr_poly_cxt_txr(&cxt, PVR_LIST_PT_POLY,
                       PVR_TXRFMT_RGB565 | PVR_TXRFMT_TWIDDLED |
                       PVR_TXRFMT_VQ_ENABLE, 256, 256, txr, PVR_FILTER_NONE);
    // pvr_poly_cxt_txr_mod(&cxt, PVR_LIST_PT_POLY,
    //                    PVR_TXRFMT_RGB565 | PVR_TXRFMT_TWIDDLED |
    //                    PVR_TXRFMT_VQ_ENABLE, 256, 256, txr, PVR_FILTER_NONE, PVR_TXRFMT_ARGB4444 | PVR_TXRFMT_TWIDDLED | PVR_TXRFMT_VQ_ENABLE, 256, 256,
    //                    light, PVR_FILTER_NONE);
    //cxt.blend.src = PVR_BLEND_DESTCOLOR;
    //cxt.blend.dst = PVR_BLEND_ZERO;
    pvr_poly_compile(&phdr[1], &cxt);

    // pvr_mod_compile(&mhdr, PVR_LIST_TR_MOD, PVR_MODIFIER_OTHER_POLY, PVR_CULLING_NONE);
    // pvr_mod_compile(&mhdr2, PVR_LIST_TR_MOD, PVR_MODIFIER_INCLUDE_LAST_POLY,
    //                 PVR_CULLING_NONE);

    for (int i = 0; i < 2; i++) {
        verts[i * 4 + 0].flags = PVR_CMD_VERTEX;
        verts[i * 4 + 0].x = 320.0f - 128.0f;
        verts[i * 4 + 0].y = 240.0f - 128.0f;
        verts[i * 4 + 0].z = 1.0f;
        verts[i * 4 + 0].u = 0.0f;
        verts[i * 4 + 0].v = 0.0f;

        verts[i * 4 + 1].flags = PVR_CMD_VERTEX;
        verts[i * 4 + 1].x = 320.0f + 128.0f;
        verts[i * 4 + 1].y = 240.0f - 128.0f;
        verts[i * 4 + 1].z = 1.0f;
        verts[i * 4 + 0].u = 1.0f;
        verts[i * 4 + 0].v = 0.0f;

        verts[i * 4 + 2].flags = PVR_CMD_VERTEX;
        verts[i * 4 + 2].x = 320.0f - 128.0f;
        verts[i * 4 + 2].y = 240.0f + 128.0f;
        verts[i * 4 + 2].z = 1.0f;
        verts[i * 4 + 0].u = 0.0f;
        verts[i * 4 + 0].v = 1.0f;

        verts[i * 4 + 3].flags = PVR_CMD_VERTEX_EOL;
        verts[i * 4 + 3].x = 320.0f + 128.0f;
        verts[i * 4 + 3].y = 240.0f + 128.0f;
        verts[i * 4 + 3].z = 1.0f;
        verts[i * 4 + 0].u = 1.0f;
        verts[i * 4 + 0].v = 1.0f;
    }
}

static int check_start() {
    maple_device_t *cont;
    cont_state_t *state;
    static int taken = 0;

    cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

    if(cont) {
        state = (cont_state_t *)maple_dev_status(cont);

        if(!state)
            return 0;

        if(state->buttons & CONT_START)
            return 1;

        if(state->joyy < -64)
            bumpiness = CLAMP(0.0f, 1.0f, bumpiness - 0.01f);
        else if(state->joyy > 64)
            bumpiness = CLAMP(0.0f, 1.0f, bumpiness + 0.01f);
    }

    return 0;
}

static void draw_sprite(pvr_ptr_t sprite, float x, float y, float w, float h, bool is_bumped) {
    pvr_poly_cxt_t ctx;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    pvr_poly_cxt_txr(&ctx, PVR_LIST_PT_POLY,
                       PVR_TXRFMT_RGB565 | PVR_TXRFMT_TWIDDLED |
                       PVR_TXRFMT_VQ_ENABLE, 256, 256, sprite, PVR_FILTER_NONE);

    if (is_bumped) {
        ctx.blend.src = PVR_BLEND_DESTCOLOR;
        ctx.blend.dst = PVR_BLEND_ZERO;
    } else {
        ctx.blend.src = PVR_BLEND_ONE;
        ctx.blend.dst = PVR_BLEND_ONE;
    }

    pvr_poly_compile(&hdr, &ctx);

    pvr_prim(&hdr, sizeof(hdr));

    vert.argb = PVR_PACK_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
    vert.oargb = 0;

    vert.flags = PVR_CMD_VERTEX;
    vert.x = x - w;
    vert.y = y - h;
    vert.z = 1.0f;
    vert.u = 0.0f;
    vert.v = 0.0f;

    pvr_prim(&vert, sizeof(vert));

    vert.flags = PVR_CMD_VERTEX;
    vert.x = x + w;
    vert.y = y - h;
    vert.z = 1.0f;
    vert.u = 1.0f;
    vert.v = 0.0f;

    pvr_prim(&vert, sizeof(vert));

    vert.flags = PVR_CMD_VERTEX;
    vert.x = x - w;
    vert.y = y + h;
    vert.z = 1.0f;
    vert.u = 0.0f;
    vert.v = 1.0f;

    pvr_prim(&vert, sizeof(vert));

    vert.flags = PVR_CMD_VERTEX_EOL;
    vert.x = x + w;
    vert.y = y + h;
    vert.z = 1.0f;
    vert.u = 1.0f;
    vert.v = 1.0f;

    pvr_prim(&vert, sizeof(vert));
}

static void draw_bump(pvr_ptr_t sprite, float x, float y, float w, float h) {
    pvr_poly_cxt_t ctx;
    pvr_poly_hdr_t hdr;
    pvr_vertex_t vert;

    Vector2_t pos = {.x = x, y = y};

    // float angle = ((float)(++counter % 240) / 240.0f) * (F_PI * 2.0f);
    float angle = angle_between(&pos, &light_pos);
    bumpiness = CLAMP(0.2f, 1.0f, distance_from(&pos, &light_pos) / 200.0f);

    pvr_poly_cxt_txr(&ctx, PVR_LIST_OP_POLY,
                       PVR_TXRFMT_BUMP | PVR_TXRFMT_TWIDDLED, 256, 256, sprite,
                       PVR_FILTER_NONE);

    ctx.gen.specular = PVR_SPECULAR_ENABLE;
    ctx.txr.env = PVR_TXRENV_DECAL;

    pvr_poly_compile(&hdr, &ctx);

    pvr_prim(&hdr, sizeof(hdr));

    vert.oargb = pvr_pack_bump(bumpiness, F_PI / 4.0f, angle);
    vert.argb = 0;

    vert.flags = PVR_CMD_VERTEX;
    vert.x = x - w;
    vert.y = y - h;
    vert.z = 1.0f;
    vert.u = 0.0f;
    vert.v = 0.0f;

    pvr_prim(&vert, sizeof(vert));

    vert.flags = PVR_CMD_VERTEX;
    vert.x = x + w;
    vert.y = y - h;
    vert.z = 1.0f;
    vert.u = 1.0f;
    vert.v = 0.0f;

    pvr_prim(&vert, sizeof(vert));

    vert.flags = PVR_CMD_VERTEX;
    vert.x = x - w;
    vert.y = y + h;
    vert.z = 1.0f;
    vert.u = 0.0f;
    vert.v = 1.0f;

    pvr_prim(&vert, sizeof(vert));

    vert.flags = PVR_CMD_VERTEX_EOL;
    vert.x = x + w;
    vert.y = y + h;
    vert.z = 1.0f;
    vert.u = 1.0f;
    vert.v = 1.0f;

    pvr_prim(&vert, sizeof(vert));
}

static void do_frame() {
    pvr_modifier_vol_t mod;
    pvr_vertex_t vert;
    pvr_poly_cxt_t ctx;
    pvr_poly_hdr_t hdr;
    int i = 0;

    ++counter;

    light_pos.x = 320.0f + sinf(((float)counter / 120.0f)) * 280.0f;
    light_pos.y = 240.0f + cosf(((float)counter / 120.0f)) * 200.0f;

    pvr_wait_ready();
    pvr_scene_begin();

    pvr_list_begin(PVR_LIST_OP_POLY);
    draw_bump(bump, 320.0f, 240.0f, 128.0f, 128.0f);
    pvr_list_finish();

    pvr_list_begin(PVR_LIST_PT_POLY);
    draw_sprite(txr, 320.0f, 240.0f, 128.0f, 128.0f, true);
    draw_sprite(light, light_pos.x, light_pos.y, 50.0f, 50.0f, false);
    pvr_list_finish();

    pvr_scene_finish();

    return;

    for (i = 0; i < 4; i++) {
        verts[i].oargb = pvr_pack_bump(bumpiness, F_PI / 4.0f, 5.0f * F_PI / 6.0f);
        verts[i].argb = 0;
    }

    pvr_wait_ready();
    pvr_scene_begin();

    // pvr_list_begin(PVR_LIST_OP_POLY);
    // pvr_prim(&phdr[0], sizeof(pvr_poly_mod_hdr_t));

    // for (i = 0; i < 4; i++) {
    //     pvr_prim(&verts[i], sizeof(pvr_vertex_t));
    // }
    // pvr_list_finish();

    // Render the modifier volume
    // pvr_list_begin(PVR_LIST_TR_MOD);
    // pvr_prim(&mhdr, sizeof(mhdr));

    // mod.flags = PVR_CMD_VERTEX_EOL;
    // mod.ax = mx;
    // mod.ay = my + 50.0f;
    // mod.az = 150.0f;
    // mod.bx = mx;
    // mod.by = my;
    // mod.bz = 150.0f;
    // mod.cx = mx + 50.0f;
    // mod.cy = my + 50.0f;
    // mod.cz = 150.0f;
    // mod.d1 = mod.d2 = mod.d3 = mod.d4 = mod.d5 = mod.d6 = 0;
    // pvr_prim(&mod, sizeof(mod));

    // pvr_prim(&mhdr2, sizeof(mhdr2));

    // mod.flags = PVR_CMD_VERTEX_EOL;
    // mod.ax = mx;
    // mod.ay = my;
    // mod.az = 150.0f;
    // mod.bx = mx + 50.0f;
    // mod.by = my + 50.0f;
    // mod.bz = 150.0f;
    // mod.cx = mx + 50.0f;
    // mod.cy = my;
    // mod.cz = 150.0f;
    // mod.d1 = mod.d2 = mod.d3 = mod.d4 = mod.d5 = mod.d6 = 0;
    // pvr_prim(&mod, sizeof(mod));
    // pvr_list_finish();

    pvr_list_begin(PVR_LIST_PT_POLY);
    pvr_prim(&phdr[1], sizeof(pvr_poly_mod_hdr_t));

    for (i = 0; i < 4; i++) {
        verts[4+i].argb = 0xffffffff;
        pvr_prim(&verts[4 + i], sizeof(pvr_vertex_t));
    }
    pvr_list_finish();

    pvr_scene_finish();
}

static pvr_init_params_t pvr_params = {
    /* Enable only opaque and punchthru polygons. */
    {
        PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_16,
        PVR_BINSIZE_16
    },
    512 * 1024
};

int main(int argc, char *argv[]) {
    gdb_init();
    printf("---KallistiOS PVR Bumpmap Example---\n");
    printf("Press A to switch between textured and non-textured mode.\n");
    printf("Use up and down on the joystick to control the bumpiness.\n");
    printf("Press Start to exit.\n");

    srand(time(NULL));

    pvr_init(&pvr_params);

    setup();

    /* Go as long as the user hasn't pressed start on controller 1. */
    while(!check_start()) {
        do_frame();
    }

    pvr_mem_free(bump);
    pvr_mem_free(txr);

    return 0;
}