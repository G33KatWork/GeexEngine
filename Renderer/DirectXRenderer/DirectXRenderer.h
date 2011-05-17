#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include "DirectXRendererExports.h"

#include <3D/Rendering/Renderer.h>
#include <Windows.h>
#include <d3d9.h>

class DIRECTXRENDERER_API DirectXRenderer : public Renderer
{
public:
    DirectXRenderer(HWND window, int width, int height);
    virtual ~DirectXRenderer();

    virtual GraphicsResourceFactory* GetGraphicsResourceFactory() { return resourceFactory; }

    virtual void Resize(int newWidth, int newHeight);
    virtual void ToggleFullscreen();

    virtual bool BeginScene();
    virtual void EndScene();

    virtual void ClearBackBuffer();
    virtual void ClearDepthBuffer();
    virtual void ClearStencilBuffer();
    virtual void ClearBuffers();

    virtual void DrawPrimitive(PrimitiveType primitiveType, unsigned int startVertex, size_t primitiveCount);
    virtual void DrawIndexedPrimitive(IndexElementType indexElementType, PrimitiveType primitiveType, unsigned int startIndex, unsigned int vertexCount, size_t primitiveCount);
    
    virtual void SwapBuffers();

	virtual void UpdateCamera(ICamera* camera);

	LPDIRECT3DDEVICE9 GetD3DDevice() { return d3dDevice; }

private:
    bool CheckCooperateLevel();

protected:
    void OnDeviceLost();
    void OnDeviceReset();

    LPDIRECT3D9 d3dObject;
    LPDIRECT3DDEVICE9 d3dDevice;
    D3DPRESENT_PARAMETERS presentationParamenters;

    GraphicsResourceFactory* resourceFactory;

    RECT oldWindowRect;

    bool deviceIsLost;
};

#endif
