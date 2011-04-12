#ifndef _DX9_TYPECONVERSIONS_H_
#define _DX9_TYPECONVERSIONS_H_

#include <d3d9.h>
#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <3D/GraphicsCardResources/IndexBuffer.h>
#include <3D/Rendering/Renderer.h>

//Renderer
D3DPRIMITIVETYPE GetD3DPrimitiveType(PrimitiveType type);

//VertexBuffer
D3DDECLTYPE GetDXDeclType(VertexElementType type, size_t componentCount);
D3DDECLUSAGE GetDXDeclUsage(VertexElementUsage usage);

//IndexBuffer
D3DFORMAT GetDXIndexType(IndexElementType type);
size_t GetDXIndexTypeSize(D3DFORMAT type);

#endif
