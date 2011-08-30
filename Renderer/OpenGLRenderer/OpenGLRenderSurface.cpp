#include "OpenGLRenderSurface.h"
#include <Common/GeexEngineException.h>

OpenGLRenderSurface::OpenGLRenderSurface()
    : fbo(NULL)
{
    glGenFramebuffers(1, &fbo);

    if(!glGetError())
        throw GeexEngineException("Error generating framebuffer object");
}

OpenGLRenderSurface::~OpenGLRenderSurface()
{
    if(fbo)
    {
        glDeleteFramebuffers(1, &fbo);
        fbo = NULL;
    }
}

void OpenGLRenderSurface::Activate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    
    if(!glGetError())
        throw GeexEngineException("Error binding framebuffer object");

}

void OpenGLRenderSurface::Deactivate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
