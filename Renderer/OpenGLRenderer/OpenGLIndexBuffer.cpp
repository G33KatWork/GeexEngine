#include "OpenGLIndexBuffer.h"
#include "OpenGLTypeConversions.h"

#include <3D/Rendering/GeexRendererException.h>

OpenGLIndexBuffer::OpenGLIndexBuffer(size_t indexCount, IndexElementType type)
    : IndexBuffer(indexCount, type),
    indexBuffer(0)
{
    glGenBuffers(1, &indexBuffer);

    if(glGetError())
        throw new GeexRendererException("Creation of index buffer failed");
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    if(indexBuffer > 0)
        glDeleteBuffers(1, &indexBuffer);
}

void OpenGLIndexBuffer::Activate()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

void OpenGLIndexBuffer::Deactivate()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::SetData(void* data)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * GetGLIndexTypeSize(GetGLIndexType(this->elementType)), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
