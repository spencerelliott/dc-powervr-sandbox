#ifndef __CORE_H__
#define __CORE_H__

#include <arch/types.h>

#define UNIM_VERSION 0x07E40001 // High byte is year (2020), low byte is revision (1)

typedef struct {
    int canvas_width;
    int canvas_height;
    int spritesheet_width;
    int spritesheet_height;
} unim_scene_t;

typedef struct {

} unim_clip_t;

typedef struct {

} unim_triggers_t;

typedef struct {

} unim_sprite_t;

typedef struct {

} unim_animation_data_t;

typedef struct {

} unim_track_object_t;

typedef struct {
    unim_scene_t scene;
    uint16 max_sprites;
    unim_clip_t *clips;
    unim_triggers_t *triggers;
    unim_sprite_t *sprites;
    unim_animation_data_t **animation_data;
    unim_track_object_t *track_objects;
} unim_t;

unim_t unim_init(void);

#endif