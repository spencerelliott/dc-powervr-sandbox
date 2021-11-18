#ifndef __RENDERER_DC_H__
#define __RENDERER_DC_H__

#include "renderer.h"

class DreamcastRenderer : virtual public Renderer {
    public:
        void Init();
        void Resize(unsigned int width, unsigned int height);
        void DrawSprite();
};

#endif