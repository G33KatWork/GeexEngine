#ifndef _DXTEXTURE_H_
#define _DXTEXTURE_H_

#include <3D/GraphicsCardResources/Texture.h>

#include <d3d9.h>
#include <d3dx9.h>

class DirectXTexture : public Texture
{
public:
    DirectXTexture(IDirect3DDevice9* device, void* textureData);
    DirectXTexture(IDirect3DDevice9* device, const char* textureFilename);
    virtual ~DirectXTexture();

    LPDIRECT3DTEXTURE9 GetDirectXTexture() { return this->dxTexture; }

private:
    LPDIRECT3DTEXTURE9 dxTexture;
    IDirect3DDevice9* device;

};

#endif
