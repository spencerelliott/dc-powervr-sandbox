#ifndef __SCENE_H__
#define __SCENE_H__

#include "../components/actor.h"

class Scene {
    public:
        Scene(void);
        void AddActor(Actor* const actor);
};

#endif