#ifndef _DX9_VERTEXBUFFER_H_
#define _DX9_VERTEXBUFFER_H_

#include "DirectXRendererExports.h"

#include <3D/GraphicsCardResources/VertexBuffer.h>
#include <d3d9.h>

class DIRECTXRENDERER_API DirectX9VertexBuffer : public VertexBuffer
{
protected:
    IDirect3DDevice9 *device;
    IDirect3DVertexDeclaration9 *vertexDeclaration;
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

    void BuildDirect3DVertexDeclaration9();

public:
    DirectX9VertexBuffer(IDirect3DDevice9 *device, size_t vertexCount, VertexBufferFormat& format);
    virtual ~DirectX9VertexBuffer();

    virtual void Activate();
    virtual void Deactivate();
    virtual void SetData(void* data);
};

#endif
