#ifndef __RENDER_H__
#define __RENDER_H__

#include "platforms.h"

#if UNIM_PLATFORM == PLATFORM_DREAMCAST
#   include "dc/render.h"
#elif UNIM_PLATFORM == PLATFORM_PC
#   include "pc/render.h"
#endif

#endif