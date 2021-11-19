#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "../custom_types.h"

class Scene;

class Actor {
    public:
        friend class Scene;

        Actor(void);

        /**
         * @brief Sets the parent of this actor. The position of this actor
         *  will be based on the parent's position.
         * 
         * @param parent The Actor to attach to
         * @return Actor& This object to allow chaining
         */
        Actor& SetParent(Actor* const parent);

        /**
         * @brief Sets the current position of this object. The position will be
         *  relative to the parent, if set.
         * 
         * @param x The x position in the scene
         * @param y The y position in the scene
         * @param z The z position in the scene
         * @return Actor& This object to allow chaining
         */
        Actor& SetPosition(float x, float y, float z);

        virtual void Update(float delta) {};
        virtual void Draw() {};
    private:
        void AttachScene(Scene* const scene);
        void DetachScene(void);

        Scene* attached_scene = nullptr;
        Actor* parent = nullptr;
        Vector3_t position;
};

#endif