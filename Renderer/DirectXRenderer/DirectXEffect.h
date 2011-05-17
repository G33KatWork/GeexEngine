#ifndef _DXEFFECT_H_
#define _DXEFFECT_H_

#include "DirectXRendererExports.h"

#include <3D/GraphicsCardResources/Effect.h>
#include "DirectXResettableResource.h"

#include <d3d9.h>
#include <d3dx9.h>

class DIRECTXRENDERER_API DirectXEffect : public Effect, DirectXResettableResource
{
public:
    DirectXEffect(IDirect3DDevice9* device, void* code);
    DirectXEffect(IDirect3DDevice9* device, const char* sourceCode);
    DirectXEffect(IDirect3DDevice9* device, const char* sourceCode, bool fromFile);
    virtual ~DirectXEffect();

    void SetTechniqueByName(const char* name);

    virtual void Begin();
    virtual void End();

    //returns true if there is a next pass
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

    //DirectXResettableResource members
    virtual void OnDeviceLost();
    virtual void OnDeviceReset();

private:
    ID3DXEffect* dxEffect;
    IDirect3DDevice9* device;

    UINT totalPasses;
    UINT currentPass;

    //prevent copying
    DirectXEffect(const DirectXEffect& other) {}
};

#endif
