#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Math/Matrix4.h>

class Technique;

class Effect
{
public:
    virtual ~Effect() {}

protected:
    Effect() {}

public:
    virtual void SetTechniqueByName(const char* name) = 0;

    virtual unsigned int Begin() = 0;
    virtual void BeginPass(unsigned int passNum) = 0;

    virtual void End() = 0;
    virtual void EndPass() = 0;


    //TODO: Replace this with a constant- oder texture-buffer later
    //Could be necessary, when we want DX11: http://msdn.microsoft.com/en-us/library/bb509581(v=vs.85).aspx
    //All other backends then emulate such a behaviour transparently
    /*virtual int GetInt(const char* name) = 0;
    virtual float GetFloat(const char* name) = 0;
    virtual bool GetBool(const char* name) = 0;
    virtual Vector2 GetVector2(const char* name) = 0;
    virtual Vector3 GetVector3(const char* name) = 0;
    virtual Vector4 GetVector4(const char* name) = 0;
    virtual Matrix4 GetMatrix(const char* name) = 0;*/

    /*virtual void SetInt(const char* name, int i) = 0;
    virtual void SetFloat(const char* name, float f) = 0;
    virtual void SetBool(const char* name, bool b) = 0;
    virtual void SetVector2(const char* name, Vector2 v) = 0;
    virtual void SetVector3(const char* name, Vector3 v) = 0;
    virtual void SetVector4(const char* name, Vector4 v) = 0;*/
    virtual void SetMatrix(const char* name, Matrix4& m) = 0;
};

#endif
