#include "CgEffect.h"
#include <3D/GraphicsCardResources/GeexShaderException.h>

CgEffect::CgEffect(CGcontext context, void* code)
    :effect(NULL),
    context(context),
    activeTechnique(NULL),
    currentPass(NULL),
    nextPass(NULL)
{
    throw new GeexEngineException("Not yet implemented");
}

CgEffect::CgEffect(CGcontext context, const char* sourceCode)
    : effect(NULL),
    context(context),
    activeTechnique(NULL),
    currentPass(NULL),
    nextPass(NULL)
{
    effect = cgCreateEffect(context, sourceCode, NULL);

    CGerror error;
    const char* errorStr = cgGetLastErrorString(&error);

    if(error)
        throw new GeexShaderException("CG Effect creation failed", errorStr);
}

CgEffect::CgEffect(CGcontext context, const char* filename, bool fromFile)
    : effect(NULL),
    context(context),
    activeTechnique(NULL),
    currentPass(NULL),
    nextPass(NULL)
{
    effect = cgCreateEffectFromFile(context, filename, NULL);

    CGerror error;
    const char* errorStr = cgGetLastErrorString(&error);

    if(error)
        throw new GeexShaderException("CG Effect creation failed", errorStr);
}

CgEffect::~CgEffect()
{
    if(effect)
    {
        cgDestroyEffect(effect);
        effect = NULL;
    }
}

void CgEffect::SetTechniqueByName(const char* name)
{
    CGtechnique tech = cgGetFirstTechnique(effect);
    
    while(tech)
    {
        if(!strcmp(cgGetTechniqueName(tech), name))
            break;

        tech = cgGetNextTechnique(tech);
    }

    this->activeTechnique = tech;
}

void CgEffect::Begin()
{
    this->nextPass = cgGetFirstPass(this->activeTechnique);
    this->currentPass = NULL;
}

void CgEffect::End()
{
    this->currentPass = NULL;
    this->nextPass = NULL;
}

bool CgEffect::ExecutePass()
{
    if(this->currentPass != NULL)
        cgResetPassState(this->currentPass);

    this->currentPass = this->nextPass;

    if(this->currentPass != NULL)
        cgSetPassState(this->currentPass);

    this->nextPass = cgGetNextPass(this->nextPass);

    return this->currentPass != NULL;
}

void CgEffect::GetInt(const char* name, int* i)
{
    cgGetParameterValueic(this->retrieveParameter(name), 1, i);
}

void CgEffect::GetFloat(const char* name, float* f)
{
    cgGetParameterValuefc(this->retrieveParameter(name), 1, f);
}

void CgEffect::GetBool(const char* name, bool* b)
{
    int i;
    cgGetParameterValueic(this->retrieveParameter(name), 1, &i);

    *b = (i != 0);
}

void CgEffect::GetVector(const char* name, Vector2* v)
{
    float values[2];
    cgGetParameterValuefc(this->retrieveParameter(name), 2, values);

    *v = Vector2(values[0], values[1]);
}

void CgEffect::GetVector(const char* name, Vector3* v)
{
    float values[3];
    cgGetParameterValuefc(this->retrieveParameter(name), 3, values);

    *v = Vector3(values[0], values[1], values[2]);
}

void CgEffect::GetVector(const char* name, Vector4* v)
{
    float values[4];
    cgGetParameterValuefc(this->retrieveParameter(name), 4, values);

    *v = Vector4(values[0], values[1], values[2], values[4]);
}

void CgEffect::GetMatrix(const char* name, Matrix4* m)
{
    float values[16];
    cgGetMatrixParameterfc(this->retrieveParameter(name), values);

    *m = Matrix4(values);
}

void CgEffect::SetInt(const char* name, int i)
{
    cgSetParameter1i(this->retrieveParameter(name), i);
}

void CgEffect::SetFloat(const char* name, float f)
{
    cgSetParameter1f(this->retrieveParameter(name), f);
}

void CgEffect::SetBool(const char* name, bool b)
{
    cgSetParameter1i(this->retrieveParameter(name), b ? 1 : 0);
}

void CgEffect::SetVector(const char* name, Vector2& v)
{
    cgSetParameter2f(this->retrieveParameter(name), v.GetX(), v.GetY());
}

void CgEffect::SetVector(const char* name, Vector3& v)
{
    cgSetParameter3f(this->retrieveParameter(name), v.GetX(), v.GetY(), v.GetZ());
}

void CgEffect::SetVector(const char* name, Vector4& v)
{
    cgSetParameter4f(this->retrieveParameter(name), v.GetX(), v.GetY(), v.GetZ(), v.GetW());
}

void CgEffect::SetMatrix(const char* name, Matrix4& m)
{
    cgSetMatrixParameterfc(this->retrieveParameter(name), m[0]);
}

void CgEffect::SetTexture(const char* name, Texture* t)
{
    
}

CGparameter CgEffect::retrieveParameter(const char* name)
{
    CGparameter param = cgGetNamedEffectParameter(effect, name);
    if(!param)
        throw new GeexShaderException("Parameter doesn't exist");

    return param;
}
