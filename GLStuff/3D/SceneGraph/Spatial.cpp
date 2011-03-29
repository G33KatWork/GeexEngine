#include <3D/SceneGraph/Spatial.h>

Spatial::Spatial(Spatial* parent)
    : localTransformation(Matrix4::Identity()),
    worldTransformation(Matrix4::Identity()),
    parent(parent)
{ }
