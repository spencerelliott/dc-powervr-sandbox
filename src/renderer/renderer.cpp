#ifdef DREAMCAST
#include <kos.h>
#include "GL/glkos.h"
#endif

#include "GL/gl.h"
#include "GL/glu.h"

#include "renderer.h"

void Renderer::Init() {
    #ifdef DREAMCAST
    glKosInit();
    #endif

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 640, 0, 480);

    glMatrixMode(GL_MODELVIEW);
}

void Renderer::Resize(unsigned int width, unsigned int height) {

}