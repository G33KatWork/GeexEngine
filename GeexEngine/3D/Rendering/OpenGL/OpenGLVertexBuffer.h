#ifndef _OGL_VERTEXBUFFER_H_
#define _OGL_VERTEXBUFFER_H_

#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <3D/Rendering/OpenGL/OpenGLHeader.h>

class OpenGLVertexBuffer : public VertexBuffer
{
protected:
    GLuint vertexBuffer;

public:
    OpenGLVertexBuffer(size_t vertexCount, VertexBufferFormat& format);
    virtual ~OpenGLVertexBuffer();

    virtual void Activate();
    virtual void Deactivate();
    virtual void SetData(void* data);
};

#endif
