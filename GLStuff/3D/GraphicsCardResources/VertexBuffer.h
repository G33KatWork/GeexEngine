#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_

#include <3D/GraphicsCardResources/IGraphicsCardResource.h>
#include <list>

enum VertexElementUsage
{
    GX_VB_ELEMENT_USAGE_POSITION,
    GX_VB_ELEMENT_USAGE_NORMAL,
    GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES,
    GX_VB_ELEMENT_USAGE_COLOR,
    GX_VB_ELEMENT_USAGE_DIFFUSE,
    GX_VB_ELEMENT_USAGE_SPECULAR,
};

enum VertexElementType
{
    GX_VB_ELEMENT_TYPE_FLOAT1,
    GX_VB_ELEMENT_TYPE_FLOAT2,
    GX_VB_ELEMENT_TYPE_FLOAT3,
    GX_VB_ELEMENT_TYPE_FLOAT4,
    GX_VB_ELEMENT_TYPE_COLOR,
    GX_VB_ELEMENT_TYPE_SHORT2,
    GX_VB_ELEMENT_TYPE_SHORT4,
    GX_VB_ELEMENT_TYPE_UBYTE4,
    GX_VB_ELEMENT_TYPE_COLOR_ARGB,
    GX_VB_ELEMENT_TYPE_COLOR_ABGR,
};

class VertexElement
{
public:
    VertexElementType type;
    VertexElementUsage usage;
    size_t offset;
    size_t size;

    VertexElement() {}
    VertexElement(VertexElementType type, VertexElementUsage usage, size_t offset, size_t size)
        : type(type), usage(usage), offset(offset), size(size)
    {}

    inline bool operator==(const VertexElement& other)
    {
        return
            other.offset == offset &&
            other.size == size &&
            other.type == type &&
            other.usage == usage;
    }

    static size_t GetTypeSize(VertexElementType type);
};

class VertexBufferFormat
{
public:
    typedef std::list<VertexElement> VertexElementList;

protected:
    VertexElementList elements;

public:
    size_t GetElementCount() const { return elements.size(); }

    const VertexBufferFormat::VertexElementList& GetElements() { return elements; }
    const VertexElement* GetElements(unsigned short at);

    void AddElement(size_t offset, size_t size, VertexElementUsage usage, VertexElementType type);
    void AddElement(unsigned short at, size_t offset, size_t size, VertexElementUsage usage, VertexElementType type);
    void RemoveElement(unsigned short at);
    void RemoveAllElements() { elements.clear(); }

    size_t GetTotalVertexSize() const;
};

class VertexBuffer /*:
    public IGraphicsCardResource*/
{
protected:
    size_t vertexCount;
    VertexBufferFormat format;

    virtual ~VertexBuffer();

public:
    VertexBuffer(size_t vertexCount, VertexBufferFormat& format);

    size_t GetVertexCount() { return vertexCount; }

    /** Memory management **/
    /*virtual void Bind(Renderer* renderer) {}
    virtual void Unbind(Renderer* renderer) {}*/

    virtual void Activate() {}
    virtual void SetData(void* data) = 0;
};

//TODO: Vertex streams

#endif

