#ifndef _SPATIAL_H_
#define _SPATIAL_H_

#include <Math/Matrix4.h>

class Spatial
{
protected:
    Spatial* parent;
    Matrix4 localTransformation;
    Matrix4 worldTransformation;

    Spatial(Spatial* parent);

    /* This function has to be called if a local change happened
     * to update the world bound of all the parents in the tree
     */
    void PropagateWorldBoundChange() {}
    virtual void UpdateWorldBound() = 0;

public:
    virtual ~Spatial(void) {}

    Spatial* GetParent() const { return this->parent; }

    virtual void Update(float timeDelta) { /* TODO: Add controllers here */ }
    virtual void Draw() = 0;
};

#endif
