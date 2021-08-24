#ifndef __PLATFORM_PLATFORM_H__
#define __PLATFORM_PLATFORM_H__


class Platform {
    public:
        Platform(void);
        static Platform* const Get();
        virtual const char * const GetName() const;
        virtual void PreInit(void) {};
        virtual void Init(void) {};
        virtual void Cleanup(void) {};
    protected:
        const char * name;
    private:
        static Platform* platform;
};

#endif