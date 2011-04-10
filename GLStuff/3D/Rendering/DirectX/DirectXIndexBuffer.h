#ifndef _DX9_INDEXBUFFER_H_
#define _DX9_INDEXBUFFER_H_

#include <3D/GraphicsCardResources/IndexBuffer.h>
#include <d3d9.h>

class DirectX9IndexBuffer : public IndexBuffer
{
protected:
    IDirect3DDevice9 *device;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;

    static D3DFORMAT GetDXIndexType(IndexElementType type);

public:
    DirectX9IndexBuffer(IDirect3DDevice9 *device, size_t indexCount, IndexElementType type);
    virtual ~DirectX9IndexBuffer();

    virtual void Activate();
    virtual void Deactivate();
    virtual void SetData(void* data);
};

#endif
