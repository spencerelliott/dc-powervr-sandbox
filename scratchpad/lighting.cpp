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

#include <dc/matrix.h>

#include "quaternion.h"

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

struct float3 {
    float x, y, z;
};

#define BASIS_WEIGHT_CONSTANT 	0.282095f
#define BASIS_WEIGHT_LINEAR	0.325735f

struct SHProbe {
public:
	float coeff[4][4];
	
public:
	SHProbe();
	
public:
	void AddAmbientLight(float3 color);
	void AddDirectionalLight(float3 direction, float3 color);
	void ApplyLighting(vector_t* invecs, vector_t* outvecs, int veccnt, int vecskip);
};

SHProbe::SHProbe() : coeff { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } }
{
}

void SHProbe::AddAmbientLight(float3 color)
{
    // when storing L1 coefficients in a matrix, the fourth column of the matrix stores constant terms for R, G, and B channels.
    // we can just add ambient color to this column.
    coeff[3][0] += color.x;
    coeff[3][1] += color.y;
    coeff[3][2] += color.z;
}

void SHProbe::AddDirectionalLight(float3 direction, float3 color)
{
    // when storing L1 coefficients in a matrix, the first three columns store the directional coefficients of RGB channels for X, Y, and Z axes respectively.
    // you can think of this as storing average directional intensity of each R, G, and B.
    // this WILL of course result in ringing artifacts the more intense the directional component, but that's a known limitation of L1 spherical harmonics
    
    coeff[0][0] += direction.x * color.x * BASIS_WEIGHT_LINEAR;
    coeff[0][1] += direction.x * color.y * BASIS_WEIGHT_LINEAR;
    coeff[0][2] += direction.x * color.z * BASIS_WEIGHT_LINEAR;
    
    coeff[1][0] += direction.y * color.x * BASIS_WEIGHT_LINEAR;
    coeff[1][1] += direction.y * color.y * BASIS_WEIGHT_LINEAR;
    coeff[1][2] += direction.y * color.z * BASIS_WEIGHT_LINEAR;
    
    coeff[2][0] += direction.z * color.x * BASIS_WEIGHT_LINEAR;
    coeff[2][1] += direction.z * color.y * BASIS_WEIGHT_LINEAR;
    coeff[2][2] += direction.z * color.z * BASIS_WEIGHT_LINEAR;
	
    coeff[3][0] += color.x * BASIS_WEIGHT_CONSTANT;
    coeff[3][1] += color.y * BASIS_WEIGHT_CONSTANT;
    coeff[3][2] += color.z * BASIS_WEIGHT_CONSTANT;
}

void SHProbe::ApplyLighting(vector_t* invecs, vector_t* outvecs, int veccnt, int vecskip)
{
	// load SH probe as matrix (TODO: this doesn't ensure proper alignment, but it's just for demonstration)
	mat_load((matrix_t*)&coeff[0][0]);
	
	// invecs is surface normals, outvecs is lighting color
	mat_transform(invecs, outvecs, veccnt, vecskip);
}

static SHProbe probe;

#define X_SCALE 128.0f
#define Y_SCALE 128.0f
#define Z_SCALE 1.0f

#define X_TRANS 240.0f
#define Y_TRANS 320.0f
#define Z_TRANS 1.5f

#define TRI_COUNT   12
#define VERT_COUNT  TRI_COUNT*3

static pvr_vertex_t vertices[VERT_COUNT] = {
    {.flags = PVR_CMD_VERTEX, .x = (-1.0f * X_SCALE) + X_TRANS, .y = (-1.0f * Y_SCALE) + Y_TRANS, .z = (1.0f * Z_SCALE) + Z_TRANS, .u = 0.0f, .v = 0.0f, .argb = 0xFF222222},
    {.flags = PVR_CMD_VERTEX, .x = (1.0f * X_SCALE) + X_TRANS, .y = (-1.0f * Y_SCALE) + Y_TRANS, .z = (1.0f * Z_SCALE) + Z_TRANS, .u = 1.0f, .v = 0.0f, .argb = 0xFFFFFFFF},
    {.flags = PVR_CMD_VERTEX, .x = (1.0f * X_SCALE) + X_TRANS, .y = (1.0f * Y_SCALE) + Y_TRANS, .z = (1.0f * Z_SCALE) + Z_TRANS, .u = 1.0f, .v = 1.0f, .argb = 0xFFAAAAAA},
    {.flags = PVR_CMD_VERTEX, .x = (-1.0f * X_SCALE) + X_TRANS, .y = (1.0f * Y_SCALE) + Y_TRANS, .z = (1.0f * Z_SCALE) + Z_TRANS, .u = 0.0f, .v = 1.0f, .argb = 0xFF111111},

    {.flags = PVR_CMD_VERTEX, .x = (-1.0f * X_SCALE) + X_TRANS, .y = (-1.0f * Y_SCALE) + Y_TRANS, .z = (-1.0f * Z_SCALE) + Z_TRANS, .u = 0.0f, .v = 0.0f, .argb = 0xFFFFFFFF},
    {.flags = PVR_CMD_VERTEX, .x = (1.0f * X_SCALE) + X_TRANS, .y = (-1.0f * Y_SCALE) + Y_TRANS, .z = (-1.0f * Z_SCALE) + Z_TRANS, .u = 1.0f, .v = 0.0f, .argb = 0xFFFFFFFF},
    {.flags = PVR_CMD_VERTEX, .x = (1.0f * X_SCALE) + X_TRANS, .y = (1.0f * Y_SCALE) + Y_TRANS, .z = (-1.0f * Z_SCALE) + Z_TRANS, .u = 1.0f, .v = 1.0f, .argb = 0xFFFFFFFF},
    {.flags = PVR_CMD_VERTEX, .x = (-1.0f * X_SCALE) + X_TRANS, .y = (1.0f * Y_SCALE) + Y_TRANS, .z = (-1.0f * Z_SCALE) + Z_TRANS, .u = 0.0f, .v = 1.0f, .argb = 0xFFFFFFFF},
};

static pvr_vertex_t eol_vertex = {.flags = PVR_CMD_VERTEX_EOL, .x = (-1.0f * X_SCALE) + X_TRANS, .y = (1.0f * Y_SCALE) + Y_TRANS, .z = (1.0f * Z_SCALE) + Z_TRANS, .u = 0.0f, .v = 1.0f, .argb = 0xFF111111};

static pvr_vertex_t vert_buffer[VERT_COUNT] = {
    // Front
    vertices[0], vertices[1], vertices[2],
    vertices[2], vertices[3], vertices[0],
    // Right
    vertices[1], vertices[5], vertices[6],
    vertices[6], vertices[2], vertices[1],
    // Back
    vertices[7], vertices[6], vertices[5],
    vertices[5], vertices[4], vertices[7],
    // Left
    vertices[4], vertices[0], vertices[3],
    vertices[3], vertices[7], vertices[4],
    // Bottom
    vertices[4], vertices[5], vertices[1],
    vertices[1], vertices[0], vertices[4],
    // Top
    vertices[3], vertices[2], vertices[6],
    vertices[6], vertices[7], eol_vertex
};

static pvr_ptr_t txr;

static pvr_init_params_t pvr_params = {
    /* Enable only opaque and punchthru polygons. */
    {
        PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_16,
        PVR_BINSIZE_16
    },
    512 * 1024
};

#define SIZE 256

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
    int i;

    if(!(txr = load_kmg("/rd/bricks.kmg"))) {
        exit(EXIT_FAILURE);
    }

    probe.AddAmbientLight({.x = 1.0f, .y = 0.0f, .z = 0.0f});
    probe.AddDirectionalLight({0.5f, 0.5f, 1.0f}, {0.0f, 1.0f, 1.0f});
}

static void do_frame() {
    pvr_modifier_vol_t mod;
    pvr_vertex_t vert;
    pvr_poly_cxt_t ctx;
    pvr_poly_hdr_t hdr;
    uint8_t i;

    pvr_wait_ready();

    pvr_scene_begin();

    pvr_list_begin(PVR_LIST_OP_POLY);
    
    pvr_poly_cxt_txr(&ctx, PVR_LIST_OP_POLY, PVR_TXRFMT_RGB565 | PVR_TXRFMT_TWIDDLED | PVR_TXRFMT_VQ_ENABLE, 256, 256, txr, PVR_FILTER_NONE);
    pvr_poly_compile(&hdr, &ctx);

    pvr_prim(&hdr, sizeof(hdr));
    for (i = 0; i < VERT_COUNT; i++) {
        pvr_prim(&vert_buffer[i], sizeof(pvr_vertex_t));
    }

    pvr_list_finish();

    pvr_scene_finish();
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
    }

    return 0;
}

int main(int argc, char *argv[]) {
    //gdb_init();
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

        pvr_stats_t stats;

        pvr_get_stats(&stats);
        if (stats.vbl_count % 60 == 0) {
            dbglog(DBG_DEBUG, "3D Stats: %d VBLs, frame rate ~%f fps\n",
            stats.vbl_count, stats.frame_rate);
        }
    }

    pvr_mem_free(txr);

    return 0;
}