#ifndef _OGL_INDEXBUFFER_H_
#define _OGL_INDEXBUFFER_H_

#include <3D/GraphicsCardResources/IndexBuffer.h>
#include "OpenGLHeader.h"
#include "OpenGLRendererExports.h"

class OPENGLRENDERER_API OpenGLIndexBuffer : public IndexBuffer
{
protected:
    GLuint indexBuffer;

public:
    OpenGLIndexBuffer(size_t indexCount, IndexElementType type);
    virtual ~OpenGLIndexBuffer();

    virtual void Activate();
    virtual void Deactivate();
    virtual void SetData(void* data);
};

#endif
