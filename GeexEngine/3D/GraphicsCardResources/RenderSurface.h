#ifndef _RENDERSURFACE_H_
#define _RENDERSURFACE_H_

class RenderSurface
{
public:
    virtual ~RenderSurface() {}

protected:
    RenderSurface() {}

public:
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
};

#endif
