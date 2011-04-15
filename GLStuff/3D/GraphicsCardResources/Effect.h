#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Math/Matrix4.h>
#include <3D/GraphicsCardResources/Texture.h>

class Effect
{
public:
    virtual ~Effect() {}

protected:
    Effect() {}

public:
    virtual void SetTechniqueByName(const char* name) = 0;

    virtual void Begin() = 0;
    virtual void End() = 0;

    virtual bool ExecutePass() = 0;


    //TODO: Replace this with a constant- oder texture-buffer later
    //Could be necessary, when we want DX11: http://msdn.microsoft.com/en-us/library/bb509581(v=vs.85).aspx
    //All other backends then emulate such a behaviour transparently
    virtual void GetInt(const char* name, int* i) = 0;
    virtual void GetFloat(const char* name, float* f) = 0;
    virtual void GetBool(const char* name, bool* b) = 0;
    virtual void GetVector(const char* name, Vector2* v) = 0;
    virtual void GetVector(const char* name, Vector3* v) = 0;
    virtual void GetVector(const char* name, Vector4* v) = 0;
    virtual void GetMatrix(const char* name, Matrix4* m) = 0;

    virtual void SetInt(const char* name, int i) = 0;
    virtual void SetFloat(const char* name, float f) = 0;
    virtual void SetBool(const char* name, bool b) = 0;
    virtual void SetVector(const char* name, Vector2& v) = 0;
    virtual void SetVector(const char* name, Vector3& v) = 0;
    virtual void SetVector(const char* name, Vector4& v) = 0;
    virtual void SetMatrix(const char* name, Matrix4& m) = 0;

    virtual void SetTexture(const char* name, Texture* t) = 0;
};

#endif
