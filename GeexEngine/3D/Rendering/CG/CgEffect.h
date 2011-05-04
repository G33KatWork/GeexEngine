#ifndef _CG_EFFECT_H_
#define _CG_EFFECT_H_

#include <3D/GraphicsCardResources/Effect.h>

#include <Cg/cg.h>

class CgEffect : public Effect
{
public:
    CgEffect(CGcontext context, void* code);
    CgEffect(CGcontext context, const char* sourceCode);
    CgEffect(CGcontext context, const char* filename, bool fromFile);
    virtual ~CgEffect();

    void SetTechniqueByName(const char* name);

    virtual void Begin();
    virtual void End();

    virtual bool ExecutePass();

    virtual void GetInt(const char* name, int* i);
    virtual void GetFloat(const char* name, float* f);
    virtual void GetBool(const char* name, bool* b);
    virtual void GetVector(const char* name, Vector2* v);
    virtual void GetVector(const char* name, Vector3* v);
    virtual void GetVector(const char* name, Vector4* v);
    virtual void GetMatrix(const char* name, Matrix4* m);

    virtual void SetInt(const char* name, int i);
    virtual void SetFloat(const char* name, float f);
    virtual void SetBool(const char* name, bool b);
    virtual void SetVector(const char* name, Vector2& v);
    virtual void SetVector(const char* name, Vector3& v);
    virtual void SetVector(const char* name, Vector4& v);
    virtual void SetMatrix(const char* name, Matrix4& m);

    virtual void SetTexture(const char* name, Texture* t);

private:
    CGeffect effect;
    CGcontext context;

    CGtechnique activeTechnique;
    CGpass currentPass;
    CGpass nextPass;

    //prevent copying
    CgEffect(const CgEffect& other) {}

    CGtechnique retrieveTechnique(const char* name);
    CGparameter retrieveParameter(const char* name);
};

#endif
