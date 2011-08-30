#include "OpenGLVertexBuffer.h"
#include "OpenGLTypeConversions.h"

#include <3D/Rendering/GeexRendererException.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(size_t vertexCount, VertexBufferFormat& format)
    : VertexBuffer(vertexCount, format),
    vertexBuffer(0)
{
    glGenBuffers(1, &vertexBuffer);

    if(glGetError())
        throw GeexRendererException("Creation of vertex buffer failed");
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    if(vertexBuffer > 0)
        glDeleteBuffers(1, &vertexBuffer);
}

void OpenGLVertexBuffer::Activate()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    GLuint index = 0;
    for(VertexBufferFormat::VertexElementList::const_iterator curElement = format.GetElements().begin(); curElement != format.GetElements().end(); curElement++)
    {
        glVertexAttribPointer(index, (*curElement).componentCount, GetGLVertexDeclType((*curElement).type), GL_FALSE, format.GetTotalVertexSize(), (void*)(*curElement).offset);
        glEnableVertexAttribArray(index);

        index++;
        
#if 0
        switch((*curElement).usage)
        {
        case GX_VB_ELEMENT_USAGE_POSITION:
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(
                (*curElement).componentCount,
                GetGLVertexDeclType((*curElement).type),
                format.GetTotalVertexSize(),
                (void*)(*curElement).offset
            );
            break;

        case GX_VB_ELEMENT_USAGE_NORMAL:
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(
                GetGLVertexDeclType((*curElement).type),
                format.GetTotalVertexSize(),
                (void*)(*curElement).offset
            );
            break;

        case GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES:
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);    //FIXME: Is this right? I doubt it. What is with different texture units?
            //TODO: implement
            throw GeexRendererException("Not implemented");
            break;

        case GX_VB_ELEMENT_USAGE_COLOR:
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(
                (*curElement).componentCount,
                GetGLVertexDeclType((*curElement).type),
                format.GetTotalVertexSize(),
                (void*)(*curElement).offset
            );
            break;
        }
#endif
    }
}

void OpenGLVertexBuffer::Deactivate()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint index = 0;
    for(VertexBufferFormat::VertexElementList::const_iterator curElement = format.GetElements().begin(); curElement != format.GetElements().end(); curElement++)
    {
        glDisableVertexAttribArray(index);
        index++;

#if 0
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
            throw GeexRendererException("Not implemented");
            break;

        case GX_VB_ELEMENT_USAGE_COLOR:
            glDisableClientState(GL_COLOR_ARRAY);
            break;
        }
#endif
    }
}

void OpenGLVertexBuffer::SetData(void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * format.GetTotalVertexSize(), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
