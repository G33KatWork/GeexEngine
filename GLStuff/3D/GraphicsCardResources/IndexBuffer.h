#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_

#include <3D/GraphicsCardResources/IGraphicsCardResource.h>

enum IndexElementType
{
    GX_IB_ELEMENT_TYPE_UINT16,
    GX_IB_ELEMENT_TYPE_UINT32,
};

class IndexBuffer /*:
    public IGraphicsCardResource*/
{
protected:
    size_t indexCount;
    IndexElementType elementType;

    virtual ~IndexBuffer() {}

public:
    IndexBuffer(size_t indexCount, IndexElementType type)
        : indexCount(indexCount),
        elementType(type)
    { }

    size_t GetIndexCount() const { return indexCount; }
    IndexElementType GetIndexElementType() const { return elementType; }

    /** Memory management **/
    /*virtual void Bind(Renderer* renderer) {}
    virtual void Unbind(Renderer* renderer) {}*/

    virtual void Activate() {}
    virtual void Deactivate() {}
    virtual void SetData(void* data) = 0;
};

#endif

