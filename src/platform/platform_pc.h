#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__

#include "platform.h"

class PcPlatform : virtual public Platform {
    public:
        PcPlatform();
        void Init(void);
        bool ProcessFrame();
        void Cleanup(void);
};

#endif