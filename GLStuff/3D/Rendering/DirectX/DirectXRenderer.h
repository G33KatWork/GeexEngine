#ifndef _DIRECTXRENDERER_H_
#define _DIRECTXRENDERER_H_

#include <3D/Rendering/Renderer.h>
#include <Windows.h>
#include <d3d9.h>

class DirectXRenderer : public Renderer
{
public:
    DirectXRenderer(HWND window, int width, int height);
    virtual ~DirectXRenderer() {}

    virtual void Resize(int newWidth, int newHeight);
    virtual void ToggleFullscreen();

    virtual bool BeginScene();
    virtual void EndScene();

    virtual void ClearBackBuffer();
    virtual void ClearDepthBuffer();
    virtual void ClearStencilBuffer();
    virtual void ClearBuffers();

    virtual void SwapBuffers();

    virtual void SetWorldMatrix(Matrix4 m);
    virtual void SetViewMatrix(Matrix4 m);
    virtual void SetProjectionMatrix(Matrix4 m);

	virtual void UpdateCamera(ICamera* camera);

	//FIXME: remove this when we have a real drawing interface
	LPDIRECT3DDEVICE9 GetDevice() { return d3dDevice; }

private:
    bool CheckCooperateLevel();

protected:
    void OnDeviceLost();
    void ResetDevice();

    D3DMATRIX ToD3DMatrix(Matrix4 m);

    LPDIRECT3D9 d3dObject;
    LPDIRECT3DDEVICE9 d3dDevice;
    D3DPRESENT_PARAMETERS presentationParamenters;

    RECT oldWindowRect;

    D3DMATRIX worldMatrix;
    D3DMATRIX viewMatrix;
    D3DMATRIX projectionMatrix;

    bool deviceIsLost;
};

#endif
