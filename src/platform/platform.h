#ifndef __PLATFORM_PLATFORM_H__
#define __PLATFORM_PLATFORM_H__


class Platform {
    public:
        Platform(void);
        static Platform* const Get();
        virtual const char * const GetName() const;
        virtual void PreInit(void) {};
        virtual void Init(void) {};

        /**
         * @brief Processes input and other platform-specific data before the game processes the frame
         * 
         * @return true If the game should continue to run, false If the game should shutdown
         */
        virtual bool ProcessFrame();
        
        virtual void Cleanup(void) {};
    protected:
        const char * name;
    private:
        static Platform* platform;
};

#endif