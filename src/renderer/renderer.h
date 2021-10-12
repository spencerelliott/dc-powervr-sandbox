#ifndef __RENDERER_H__
#define __RENDERER_H__

class Renderer {
    public:
        void Init();
        void Resize(unsigned int width, unsigned int height);
        void DrawSprite();
};

#endif