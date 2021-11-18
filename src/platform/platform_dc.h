#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__

#include "platform.h"

class DreamcastPlatform : virtual public Platform {
    public:
        DreamcastPlatform();
        void Init(void);
        bool ProcessFrame();
        void Cleanup(void);
};

#endif