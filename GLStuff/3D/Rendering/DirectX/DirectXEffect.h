#ifndef _DXEFFECT_H_
#define _DXEFFECT_H_

#include <3D/GraphicsCardResources/Effect.h>

#include <d3d9.h>
#include <d3dx9.h>

class DirectXEffect : public Effect
{
public:
    DirectXEffect(IDirect3DDevice9* device, void* code);
    DirectXEffect(IDirect3DDevice9* device, const char* sourceCode);
    virtual ~DirectXEffect();

    void SetTechniqueByName(const char* name);

    virtual unsigned int Begin();
    virtual void BeginPass(unsigned int passNum);

    virtual void End();
    virtual void EndPass();

private:
    ID3DXEffect* dxEffect;
    IDirect3DDevice9* device;

};

#endif
