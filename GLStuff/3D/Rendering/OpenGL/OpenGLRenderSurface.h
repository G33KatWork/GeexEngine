#ifndef _OGLRENDERSURFACE_H_
#define _OGLRENDERSURFACE_H_

#include <3D/Rendering/OpenGL/OpenGLHeader.h>
#include <3D/GraphicsCardResources/RenderSurface.h>

class OpenGLRenderSurface : public RenderSurface
{
public:
    OpenGLRenderSurface();
    virtual ~OpenGLRenderSurface();

    virtual void Activate();
    virtual void Deactivate();

private:
    GLuint fbo;

    //prevent copying
    OpenGLRenderSurface(const OpenGLRenderSurface& other) {}
};

#endif
