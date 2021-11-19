#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "actor.h"

class Light : public Actor {
    public:
        void Update(float delta) {};
        void Draw() {};
};

#endif