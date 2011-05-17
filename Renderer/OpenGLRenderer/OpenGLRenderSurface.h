#ifndef _OGLRENDERSURFACE_H_
#define _OGLRENDERSURFACE_H_

#include <3D/GraphicsCardResources/RenderSurface.h>

#include "OpenGLHeader.h"
#include "OpenGLRendererExports.h"

class OPENGLRENDERER_API OpenGLRenderSurface : public RenderSurface
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
