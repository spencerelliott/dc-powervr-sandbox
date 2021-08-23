#ifndef __PLATFORM_PLATFORM_H__
#define __PLATFORM_PLATFORM_H__


class Platform {
    public:
        static Platform* Get();
        virtual void PreInit(void) {};
        virtual void Init(void) {};
        virtual void Cleanup(void) {};
    private:
        const char * const name;
        static Platform* platform;
};

#endif