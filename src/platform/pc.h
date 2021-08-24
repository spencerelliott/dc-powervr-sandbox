#ifndef __PLATFORM_PC_H__
#define __PLATFORM_PC_H__

#include "platform.h"
#include "pc.h"

class PcPlatform : virtual public Platform {
    public:
        PcPlatform();
        void PreInit(void);
        void Init(void);
        void Cleanup(void);
};

#endif