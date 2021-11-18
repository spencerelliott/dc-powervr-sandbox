#ifndef __RENDERER_H__
#define __RENDERER_H__

class Renderer {
    public:
        /**
         * @brief Retrieves the renderer for this platform.
         * 
         * @return Renderer* const The pointer to the renderer
         */
        static Renderer* const Get();

        /**
         * @brief Initializes the renderer. This should be called before drawing.
         * 
         */
        virtual void Init();

        /**
         * @brief Resizes the viewport if the platform supports it.
         * 
         * @param width The new width of the viewport
         * @param height The new height of the viewport
         */
        virtual void Resize(unsigned int width, unsigned int height);
        virtual void DrawSprite();
    private:
        static Renderer* renderer;
};

#endif