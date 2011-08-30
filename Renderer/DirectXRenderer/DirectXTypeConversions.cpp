#include "DirectXTypeConversions.h"
#include <Common/GeexEngineException.h>

D3DPRIMITIVETYPE GetD3DPrimitiveType(PrimitiveType type)
{
    switch(type)
    {
    case PRIMTYPE_LINELIST:
        return D3DPT_LINELIST;
    case PRIMTYPE_LINESTRIP:
        return D3DPT_LINESTRIP;
    case PRIMTYPE_POINTLIST:
        return D3DPT_POINTLIST;
    case PRIMTYPE_TRIANGLEFAN:
        return D3DPT_TRIANGLEFAN;
    case PRIMTYPE_TRIANGLELIST:
        return D3DPT_TRIANGLELIST;
    case PRIMTYPE_TRIANGLESTRIP:
        return D3DPT_TRIANGLESTRIP;
    }

    throw GeexEngineException("Invalid PrimitiveType passed");
}

D3DDECLTYPE GetDXDeclType(VertexElementType type, size_t componentCount)
{
    switch(type)
    {
    case GX_VB_ELEMENT_TYPE_FLOAT:
        if(componentCount == 1)
            return D3DDECLTYPE_FLOAT1;
        else if (componentCount == 2)
            return D3DDECLTYPE_FLOAT2;
        else if (componentCount == 3)
            return D3DDECLTYPE_FLOAT3;
        else if (componentCount == 4)
            return D3DDECLTYPE_FLOAT4;

    case GX_VB_ELEMENT_TYPE_SHORT:
        if(componentCount == 2)
            return D3DDECLTYPE_SHORT2;
        else if (componentCount == 4)
            return D3DDECLTYPE_SHORT4;

    case GX_VB_ELEMENT_TYPE_UBYTE:
        if (componentCount == 4)
            return D3DDECLTYPE_UBYTE4;
    }

    throw GeexEngineException("Unknown VertexElementType and componentCount pair supplied");
}

D3DDECLUSAGE GetDXDeclUsage(VertexElementUsage usage)
{
    switch(usage)
    {
    case GX_VB_ELEMENT_USAGE_POSITION:
        return D3DDECLUSAGE_POSITION;
    case GX_VB_ELEMENT_USAGE_NORMAL:
        return D3DDECLUSAGE_NORMAL;
    case GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES:
        return D3DDECLUSAGE_TEXCOORD;
    case GX_VB_ELEMENT_USAGE_COLOR:
        return D3DDECLUSAGE_COLOR;
    /*case GX_VB_ELEMENT_USAGE_DIFFUSE:
        return D3DDECLUSAGE_COLOR;
    case GX_VB_ELEMENT_USAGE_SPECULAR:
        return D3DDECLUSAGE_COLOR;*/
    }

    throw GeexEngineException("Unknown VertexElementUsage supplied");
}

D3DFORMAT GetDXIndexType(IndexElementType type)
{
    switch(type)
    {
    case GX_IB_ELEMENT_TYPE_UINT16:
        return D3DFMT_INDEX16;
    case GX_IB_ELEMENT_TYPE_UINT32:
        return D3DFMT_INDEX32;
    }

    throw GeexEngineException("Unknown IndexElementType supplied");
}

size_t GetDXIndexTypeSize(D3DFORMAT type)
{
    switch(type)
    {
    case D3DFMT_INDEX16:
        return sizeof(unsigned short);
    case D3DFMT_INDEX32:
        return sizeof(unsigned int);
    }

    throw GeexEngineException("Unappropriate D3DFORMAT supplied");
}
