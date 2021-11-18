#ifndef __PLATFORM_PLATFORM_H__
#define __PLATFORM_PLATFORM_H__


class Platform {
    public:
        Platform(void);

        /**
         * @brief Retrieves the platform object.
         * 
         * @return Platform* const The pointer to the platform
         */
        static Platform* const Get();

        /**
         * @brief Get the name of the platform.
         * 
         * @return const char* const The string name of the platform
         */
        virtual const char * const GetName() const;

        /**
         * @brief Initializes the platform. This would usually set up anything specific
         *  relating to the filesystem or hardware such as controllers.
         * 
         */
        virtual void Init(void) {};

        /**
         * @brief Processes input and other platform-specific data before the game processes the frame.
         * 
         * @return true If the game should continue to run, false If the game should shutdown
         */
        bool ProcessFrame() { return false; }
        
        /**
         * @brief Cleans up any objects or hardware before shutting down.
         * 
         */
        virtual void Cleanup(void) {};
    protected:
        const char * name;
    private:
        static Platform* platform;
};

#endif