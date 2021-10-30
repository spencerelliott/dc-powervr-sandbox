#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__

#include "platform.h"
#include "pc.h"

class DreamcastPlatform : virtual public Platform {
    public:
        DreamcastPlatform();
        void PreInit(void);
        void Init(void);
        bool ProcessFrame();
        void Cleanup(void);
};

#endif