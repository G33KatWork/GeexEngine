#include "DirectXEffect.h"
#include "DirectXTexture.h"
#include <3D/GraphicsCardResources/GeexShaderException.h>

//FIXME: Upon first setting or getting of parameter, save the parameter object in some hashtable or so and use this for next gets and sets. Perhaps faster?

DirectXEffect::DirectXEffect(IDirect3DDevice9* device, void* code)
    : dxEffect(NULL),
    device(device),
    currentPass(0),
    totalPasses(0),
    DirectXResettableResource()
{
    throw GeexEngineException("Not yet implemented");
}

DirectXEffect::DirectXEffect(IDirect3DDevice9* device, const char* sourceCode)
    : dxEffect(NULL),
    device(device),
    currentPass(0),
    totalPasses(0),
    DirectXResettableResource()
{
    LPD3DXBUFFER errors = NULL;
    
    if(FAILED(D3DXCreateEffect(
        device,
        sourceCode,
        strlen(sourceCode),
        NULL,   //defines
        NULL,   //includes
        D3DXSHADER_PACKMATRIX_COLUMNMAJOR,  //TODO: Flags?
        NULL,   //EffectPool TODO: use this?
        &this->dxEffect,
        &errors
    )))
        throw GeexShaderException("Creating a DirectX effect failed", (const char*)errors->GetBufferPointer());
}

DirectXEffect::DirectXEffect(IDirect3DDevice9* device, const char* sourceCode, bool fromFile)
    : dxEffect(NULL),
    device(device),
    currentPass(0),
    totalPasses(0),
    DirectXResettableResource()
{
    LPD3DXBUFFER errors = NULL;
    if(FAILED(D3DXCreateEffectFromFile(
        device,
        sourceCode,
        NULL,   //defines
        NULL,   //includes
        D3DXSHADER_PACKMATRIX_COLUMNMAJOR,  //TODO: Flags?
        NULL,   //EffectPool TODO: use this?
        &this->dxEffect,
        &errors
    )))
        throw GeexShaderException("Creating a DirectX effect failed", (const char*)errors->GetBufferPointer());
}

DirectXEffect::~DirectXEffect()
{
    if(dxEffect)
    {
        dxEffect->Release();
        dxEffect = NULL;
    }
}

void DirectXEffect::SetTechniqueByName(const char* name)
{
    D3DXHANDLE technique = this->dxEffect->GetTechniqueByName(name);
    if(!technique)
        throw GeexShaderException("Requested technique doesn't exist");
    
    if(FAILED(this->dxEffect->SetTechnique(technique)))
        throw GeexShaderException("Switching to technique failed");
}

void DirectXEffect::Begin()
{
    if(FAILED(this->dxEffect->Begin(&totalPasses, 0)))
        throw GeexShaderException("Beginning of effect failed");
    
    currentPass = 0;
}

bool DirectXEffect::ExecutePass()
{
    //if not the first pass...
    if(currentPass > 0)
    {
        //end last pass...
        if(FAILED(this->dxEffect->EndPass()))
            throw GeexShaderException("End of shader failed");
    }

    //... and start new one if there is one left
    if(currentPass < totalPasses)
    {
        if(FAILED(this->dxEffect->BeginPass(currentPass)))
            throw GeexShaderException("Beginning of shader pass failed");
    }

    currentPass++;

    return currentPass - 1 < totalPasses;
}

void DirectXEffect::End()
{
    if(FAILED(this->dxEffect->End()))
            throw GeexShaderException("End of shader failed");
}

void DirectXEffect::GetInt(const char* name, int* i)
{
    this->dxEffect->GetInt(name, i);
}

void DirectXEffect::GetFloat(const char* name, float* f)
{
    this->dxEffect->GetFloat(name, f);
}

void DirectXEffect::GetBool(const char* name, bool* b)
{
    BOOL bo;
    this->dxEffect->GetBool(name, &bo);

    *b = bo == TRUE ? true : false;
}

void DirectXEffect::GetVector(const char* name, Vector2* v)
{
    D3DXVECTOR4 vec;
    this->dxEffect->GetVector(name, &vec);

    v->SetX(vec.x);
    v->SetY(vec.y);
}

void DirectXEffect::GetVector(const char* name, Vector3* v)
{
    D3DXVECTOR4 vec;
    this->dxEffect->GetVector(name, &vec);

    v->SetX(vec.x);
    v->SetY(vec.y);
    v->SetZ(vec.z);
}

void DirectXEffect::GetVector(const char* name, Vector4* v)
{
    D3DXVECTOR4 vec;
    this->dxEffect->GetVector(name, &vec);

    v->SetX(vec.x);
    v->SetY(vec.y);
    v->SetZ(vec.z);
    v->SetW(vec.w);
}

void DirectXEffect::GetMatrix(const char* name, Matrix4* m)
{
    D3DXMATRIX mat;
    this->dxEffect->GetMatrix(name, &mat);

    *m = Matrix4(mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
                 mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
                 mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
                 mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
    );
}

void DirectXEffect::SetInt(const char* name, int i)
{
    this->dxEffect->SetInt(name, i);
}

void DirectXEffect::SetFloat(const char* name, float f)
{
    this->dxEffect->SetFloat(name, f);
}

void DirectXEffect::SetBool(const char* name, bool b)
{
    this->dxEffect->SetBool(name, b);
}

void DirectXEffect::SetVector(const char* name, Vector2& v)
{
    D3DXVECTOR4 vector = D3DXVECTOR4(v.GetX(), v.GetY(), 0.0f, 1.0f);
    this->dxEffect->SetVector(name, &vector);
}

void DirectXEffect::SetVector(const char* name, Vector3& v)
{
    D3DXVECTOR4 vector = D3DXVECTOR4(v.GetX(), v.GetY(), v.GetZ(), 1.0f);
    this->dxEffect->SetVector(name, &vector);
}

void DirectXEffect::SetVector(const char* name, Vector4& v)
{
    D3DXVECTOR4 vector = D3DXVECTOR4(v.GetX(), v.GetY(), v.GetZ(), v.GetW());
    this->dxEffect->SetVector(name, &vector);
}

void DirectXEffect::SetMatrix(const char* name, Matrix4& m)
{
    D3DXMATRIX matrix = D3DXMATRIX(m[0]);
    HRESULT res = this->dxEffect->SetMatrix(name, &matrix);
}

void DirectXEffect::SetTexture(const char* name, Texture* t)
{
    //FIXME: Casting OK? I don't think that there will be anything else than a DX Texture arrive here
    this->dxEffect->SetTexture(name, ((DirectXTexture*)t)->GetDirectXTexture());
}

void DirectXEffect::OnDeviceLost()
{
    this->dxEffect->OnLostDevice();
}

void DirectXEffect::OnDeviceReset()
{
    this->dxEffect->OnResetDevice();
}