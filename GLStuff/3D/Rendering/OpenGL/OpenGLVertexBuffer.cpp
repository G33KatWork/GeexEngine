#include "OpenGLVertexBuffer.h"
#include <3D/Rendering/GeexRendererException.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(size_t vertexCount, VertexBufferFormat& format)
    : VertexBuffer(vertexCount, format),
    vertexBuffer(0)
{
    glGenBuffers(1, &vertexBuffer);

    if(glGetError())
        throw new GeexRendererException("Creation of vertex buffer failed");
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    if(vertexBuffer > 0)
        glDeleteBuffers(1, &vertexBuffer);
}

void OpenGLVertexBuffer::Activate()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    for(VertexBufferFormat::VertexElementList::const_iterator curElement = format.GetElements().begin(); curElement != format.GetElements().end(); curElement++)
    {
        switch((*curElement).usage)
        {
        case GX_VB_ELEMENT_USAGE_POSITION:
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer((*curElement).componentCount, GetGLDeclType((*curElement).type), format.GetTotalVertexSize(), (void*)(*curElement).offset);
            break;

        case GX_VB_ELEMENT_USAGE_NORMAL:
            glEnableClientState(GL_NORMAL_ARRAY);
            glVertexPointer((*curElement).componentCount, GetGLDeclType((*curElement).type), format.GetTotalVertexSize(), (void*)(*curElement).offset);
            break;

        case GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES:
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);    //FIXME: Is this right? I doubt it. What is with different texture units?
            //TODO: implement
            throw new GeexRendererException("Not implemented");
            break;

        case GX_VB_ELEMENT_USAGE_COLOR:
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer((*curElement).componentCount, GetGLDeclType((*curElement).type), format.GetTotalVertexSize(), (void*)(*curElement).offset);
            break;
        }
    }
}

void OpenGLVertexBuffer::Deactivate()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    for(VertexBufferFormat::VertexElementList::const_iterator curElement = format.GetElements().begin(); curElement != format.GetElements().end(); curElement++)
    {
        switch((*curElement).usage)
        {
        case GX_VB_ELEMENT_USAGE_POSITION:
            glDisableClientState(GL_VERTEX_ARRAY);
            break;

        case GX_VB_ELEMENT_USAGE_NORMAL:
            glDisableClientState(GL_NORMAL_ARRAY);
            break;

        case GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES:
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);    //FIXME: Is this right? I doubt it. What is with different texture units?
            //TODO: implement
            throw new GeexRendererException("Not implemented");
            break;

        case GX_VB_ELEMENT_USAGE_COLOR:
            glDisableClientState(GL_COLOR_ARRAY);
            break;
        }
    }
}

void OpenGLVertexBuffer::SetData(void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * format.GetTotalVertexSize(), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLenum OpenGLVertexBuffer::GetGLDeclType(VertexElementType type)
{
    switch(type)
    {
    case GX_VB_ELEMENT_TYPE_FLOAT:
        return GL_FLOAT;

    case GX_VB_ELEMENT_TYPE_SHORT:
    case GX_VB_ELEMENT_TYPE_UBYTE:
        return GL_SHORT;
    }

    throw new GeexRendererException("Unknown VertexElementType supplied");
}
