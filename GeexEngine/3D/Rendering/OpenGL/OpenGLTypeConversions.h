#ifndef _OGL_TYPECONVERSIONS_H_
#define _OGL_TYPECONVERSIONS_H_

#include <3D/Rendering/OpenGL/OpenGLHeader.h>
#include <3D/GraphicsCardResources/IndexBuffer.h>
#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <3D/Rendering/Renderer.h>

//Renderer
GLenum GetGLPrimitiveType(PrimitiveType type);

//Vertex Buffer
GLenum GetGLVertexDeclType(VertexElementType type);

//IndexBuffer
GLenum GetGLIndexType(IndexElementType type);
size_t GetGLIndexTypeSize(GLenum type);

#endif
