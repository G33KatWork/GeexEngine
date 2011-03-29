#include "DirectXVertexBuffer.h"
#include <3D/Rendering/GeexRendererException.h>

DirectX9VertexBuffer::DirectX9VertexBuffer(IDirect3DDevice9 *device, size_t vertexCount, VertexBufferFormat& format)
    : VertexBuffer(vertexCount, format),
    device(device),
    vertexDeclaration(NULL),
    vertexBuffer(NULL)
{
    this->BuildDirect3DVertexDeclaration9();

    if(FAILED(device->CreateVertexBuffer(
        vertexCount * format.GetTotalVertexSize(),
        0,  //TODO: define usage
        0,  //no FVF
        D3DPOOL_MANAGED,    //TODO: define pool
        &vertexBuffer,
        NULL
    )))
        throw new GeexRendererException("Creation of vertex buffer failed");
}

DirectX9VertexBuffer::~DirectX9VertexBuffer()
{
    if(vertexBuffer)
    {
        vertexBuffer->Release();
        vertexBuffer = NULL;
    }

    if(vertexDeclaration)
    {
        vertexDeclaration->Release();
        vertexDeclaration = NULL;
    }
}

void DirectX9VertexBuffer::Activate()
{
    if(FAILED(device->SetVertexDeclaration(vertexDeclaration)))
        throw new GeexRendererException("Setting of vertex declaration failed");

    if(FAILED(device->SetStreamSource(0, vertexBuffer, 0, format.GetTotalVertexSize())))
        throw new GeexRendererException("Setting of vertex stream source failed");
}

void DirectX9VertexBuffer::SetData(void* data)
{
    void *pVertexBuffer = NULL;
    if(FAILED(vertexBuffer->Lock(0, vertexCount * format.GetTotalVertexSize(), &pVertexBuffer, 0)))
        throw new GeexRendererException("Locking of vertex buffer failed");

    memcpy(pVertexBuffer, data, vertexCount * format.GetTotalVertexSize());

    if(FAILED(vertexBuffer->Unlock()))
        throw new GeexRendererException("Unlocking of vertex buffer failed");
}

void DirectX9VertexBuffer::BuildDirect3DVertexDeclaration9()
{
    size_t vertexElementCount = format.GetElementCount();

    LPD3DVERTEXELEMENT9 declaration = new D3DVERTEXELEMENT9[vertexElementCount + 1];
    if(!declaration)
        throw new GeexRendererException("Allocation of vertex declaration array failed");

    for(size_t i = 0; i < vertexElementCount; i++)
    {
        const VertexElement* curElement = format.GetElements(i);

        declaration[i].Stream = 0;
        declaration[i].Offset = curElement->offset;
        declaration[i].Type = GetDXDeclType(curElement->type);
        declaration[i].Method = D3DDECLMETHOD_DEFAULT;  //TODO: let user specify this crap
        declaration[i].Usage = GetDXDeclUsage(curElement->usage);
        declaration[i].UsageIndex = 0;
    }

    //Last entry for termination, see D3DDECL_END()
    declaration[vertexElementCount].Stream = 0xFF;
    declaration[vertexElementCount].Offset = 0;
    declaration[vertexElementCount].Type = D3DDECLTYPE_UNUSED;
    declaration[vertexElementCount].Method = 0;
    declaration[vertexElementCount].Usage = 0;
    declaration[vertexElementCount].UsageIndex = 0;

    HRESULT hr = device->CreateVertexDeclaration(declaration, &vertexDeclaration);
    if(FAILED(hr))
        throw new GeexRendererException("Creation of vertex declaration failed");


    delete[] declaration;
}

D3DDECLTYPE DirectX9VertexBuffer::GetDXDeclType(VertexElementType type)
{
    switch(type)
    {
    case GX_VB_ELEMENT_TYPE_COLOR:
    case GX_VB_ELEMENT_TYPE_COLOR_ABGR:
    case GX_VB_ELEMENT_TYPE_COLOR_ARGB:
        return D3DDECLTYPE_D3DCOLOR;
    case GX_VB_ELEMENT_TYPE_FLOAT1:
        return D3DDECLTYPE_FLOAT1;
    case GX_VB_ELEMENT_TYPE_FLOAT2:
        return D3DDECLTYPE_FLOAT2;
    case GX_VB_ELEMENT_TYPE_FLOAT3:
        return D3DDECLTYPE_FLOAT3;
    case GX_VB_ELEMENT_TYPE_FLOAT4:
        return D3DDECLTYPE_FLOAT4;
    case GX_VB_ELEMENT_TYPE_SHORT2:
        return D3DDECLTYPE_SHORT2;
    case GX_VB_ELEMENT_TYPE_SHORT4:
        return D3DDECLTYPE_SHORT4;
    case GX_VB_ELEMENT_TYPE_UBYTE4:
        return D3DDECLTYPE_UBYTE4;
    }

    throw new GeexRendererException("Unknown VertexElementType supplied");
}

D3DDECLUSAGE DirectX9VertexBuffer::GetDXDeclUsage(VertexElementUsage usage)
{
    switch(usage)
    {
    case GX_VB_ELEMENT_USAGE_POSITION:
        return D3DDECLUSAGE_POSITIONT;
    case GX_VB_ELEMENT_USAGE_NORMAL:
        return D3DDECLUSAGE_NORMAL;
    case GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES:
        return D3DDECLUSAGE_TEXCOORD;
    case GX_VB_ELEMENT_USAGE_COLOR:
        return D3DDECLUSAGE_COLOR;
    case GX_VB_ELEMENT_USAGE_DIFFUSE:
        return D3DDECLUSAGE_COLOR;
    case GX_VB_ELEMENT_USAGE_SPECULAR:
        return D3DDECLUSAGE_COLOR;
    }

    throw new GeexRendererException("Unknown VertexElementUsage supplied");
}
