#include "DirectXEffect.h"
#include <3D/GraphicsCardResources/GeexShaderException.h>

DirectXEffect::DirectXEffect(IDirect3DDevice9* device, void* code)
    : dxEffect(NULL),
    device(device)
{
    throw new GeexEngineException("Not yet implemented");
}

DirectXEffect::DirectXEffect(IDirect3DDevice9* device, const char* sourceCode)
    : dxEffect(NULL),
    device(device)
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
        throw new GeexShaderException("Creating a DirectX effect failed", (const char*)errors->GetBufferPointer());
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
        throw new GeexShaderException("Requested technique doesn't exist");
    
    this->dxEffect->SetTechnique(technique);
}

unsigned int DirectXEffect::Begin()
{
    UINT passes;
    if(FAILED(this->dxEffect->Begin(&passes, 0)))
        throw new GeexShaderException("Beginning of effect failed");
    
    return passes;
}

void DirectXEffect::BeginPass(unsigned int passNum)
{
    if(FAILED(this->dxEffect->BeginPass(passNum)))
        throw new GeexShaderException("Beginning of shader pass failed");
}

void DirectXEffect::End()
{
    if(FAILED(this->dxEffect->EndPass()))
        throw new GeexShaderException("End of shader failed");
}

void DirectXEffect::EndPass()
{
    if(FAILED(this->dxEffect->End()))
        throw new GeexShaderException("End of shader pass failed");
}
