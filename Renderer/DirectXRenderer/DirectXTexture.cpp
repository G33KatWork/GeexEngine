#include "DirectXTexture.h"
#include <3D/GraphicsCardResources/GeexShaderException.h>

DirectXTexture::DirectXTexture(IDirect3DDevice9* device, void* textureData)
    : dxTexture(NULL),
    device(device)
{
    throw new GeexEngineException("Not yet implemented");
}

DirectXTexture::DirectXTexture(IDirect3DDevice9* device, const char* textureFilename)
    : dxTexture(NULL),
    device(device)
{
    if(FAILED(D3DXCreateTextureFromFile(device, textureFilename, &dxTexture)))
        throw new GeexEngineException("Texture creation from file failed");
}

DirectXTexture::~DirectXTexture()
{
    if(dxTexture)
    {
        dxTexture->Release();
        dxTexture = NULL;
    }
}
