#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "actor.h"

class Sprite : public Actor {
    public:
        void Update(float delta) {};
        void Draw() {};
};

#endif