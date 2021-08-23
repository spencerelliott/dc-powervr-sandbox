#ifndef __CORE_H__
#define __CORE_H__

#ifdef DREAMCAST
#include <arch/types.h>
#else
#include <stdint-gcc.h>
#endif
#include <stdbool.h>

#include "types.h"

#define UNIM_VERSION 0x07E40001 // High byte is year (2020), low byte is revision (1)

#ifndef DREAMCAST
typedef uint16_t uint16;
#endif

enum class UnimResult {
    OK = 0,
    ERROR
};

typedef struct {
    int canvas_width;
    int canvas_height;
    int spritesheet_width;
    int spritesheet_height;
} unim_scene_t;

typedef struct {
    int start_frame;
    int duration;
    char name[30];
} unim_clip_t;

typedef struct {
    int frame;
    int index;
    char name[30];
} unim_triggers_t;

typedef struct {
    int id;
    int x;
    int y;
    int width;
    int height;
    bool rotated;
    char spare[2];
    vector2_t top_left;
    vector2_t top_right;
    vector2_t bottom_left;
    vector2_t bottom_right;
} unim_sprite_t;

typedef struct {
    int sprite_id;
    color_t color;
    color_t color_add;
    float scale_x;
    float scale_y;
    float skew_x;
    float skew_y;
    float position_x;
    float position_y;
    float position_z;
} unim_animation_data_t;

typedef struct {
    
} unim_track_object_t;

typedef struct {
    int frame;
    vector3_t position;
    vector2_t scale;
    float rotation;
} unim_track_transform_t;

typedef struct {
    unim_scene_t scene;
    uint16 max_sprites;
    unim_clip_t *clips;
    unim_triggers_t *triggers;
    unim_sprite_t *sprites;
    unim_animation_data_t **animation_data;
    unim_track_object_t *track_objects;
} unim_t;

class Unim {
    public:
        Unim(const char *, const char *);
        void Tick(void);
        UnimResult PlayAnimation(const char *);
    private:
        unim_scene_t scene;
        uint16 max_sprites;
        unim_clip_t *clips;
        unim_triggers_t *triggers;
        unim_sprite_t *sprites;
        unim_animation_data_t **animation_data;
        unim_track_object_t *track_objects;
};

#endif