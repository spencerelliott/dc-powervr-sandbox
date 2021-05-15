#ifndef __CORE_H__
#define __CORE_H__

#define UNIM_VERSION 0x07E40001 // High byte is year (2020), low byte is revision (1)

typedef struct {
    int canvas_width;
    int canvas_height;
    int spritesheet_width;
    int spritesheet_height;
} unim_scene_t;

#endif