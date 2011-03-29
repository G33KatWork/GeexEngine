#ifndef _IGRAPHICSCARDRESOURCE_H_
#define _IGRAPHICSCARDRESOURCE_H_

#include <3D/Rendering/Renderer.h>

class IGraphicsCardResource
{
protected:
    IGraphicsCardResource() {}

public:
    virtual void Bind(Renderer* renderer) = 0;
    virtual void Unbind(Renderer* renderer) = 0;
};

#endif
