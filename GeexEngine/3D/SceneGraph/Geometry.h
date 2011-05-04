#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <3D/SceneGraph/Spatial.h>

class Geometry : public Spatial
{
protected:
    Geometry(Spatial* parent);
    void UpdateWorldBound() {}

public:
    ~Geometry(void) {}

    virtual void Draw() = 0;
};

#endif _SPATIAL_H_
