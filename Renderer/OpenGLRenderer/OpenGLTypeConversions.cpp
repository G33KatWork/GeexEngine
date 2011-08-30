#include "OpenGLTypeConversions.h"
#include <Common/GeexEngineException.h>

GLenum GetGLPrimitiveType(PrimitiveType type)
{
    switch(type)
    {
    case PRIMTYPE_LINELIST:
        return GL_LINES;
    case PRIMTYPE_LINESTRIP:
        return GL_LINE_STRIP;
    case PRIMTYPE_POINTLIST:
        return GL_POINTS;
    case PRIMTYPE_TRIANGLEFAN:
        return GL_TRIANGLE_FAN;
    case PRIMTYPE_TRIANGLELIST:
        return GL_TRIANGLES;
    case PRIMTYPE_TRIANGLESTRIP:
        return GL_TRIANGLE_STRIP;
    }

    throw GeexEngineException("Invalid PrimitiveType passed");
}

GLenum GetGLVertexDeclType(VertexElementType type)
{
    switch(type)
    {
    case GX_VB_ELEMENT_TYPE_FLOAT:
        return GL_FLOAT;

    case GX_VB_ELEMENT_TYPE_SHORT:
    case GX_VB_ELEMENT_TYPE_UBYTE:
        return GL_SHORT;
    }

    throw GeexEngineException("Invalid VertexElementType supplied");
}

GLenum GetGLIndexType(IndexElementType type)
{
    switch(type)
    {
    case GX_IB_ELEMENT_TYPE_UINT16:
        return GL_UNSIGNED_SHORT;
    case GX_IB_ELEMENT_TYPE_UINT32:
        return GL_UNSIGNED_INT;
    }

    throw GeexEngineException("Invalid IndexElementType supplied");
}

size_t GetGLIndexTypeSize(GLenum type)
{
    switch(type)
    {
    case GL_UNSIGNED_SHORT:
        return sizeof(unsigned short);
    case GL_UNSIGNED_INT:
        return sizeof(unsigned int);
    }

    throw GeexEngineException("Invalid OpenGL Type supplied");
}

