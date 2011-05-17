#include "DirectXRenderer.h"
#include "DirectXResettableResource.h"
#include "DirectXTypeConversions.h"
#include "DirectXGraphicsResourceFactory.h"

#include <Common/GeexEngineException.h>

DirectXRenderer::DirectXRenderer(HWND window, int width, int height)
    : Renderer(width, height),
    deviceIsLost(false),
    resourceFactory(NULL)
{
    d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
    if(!d3dObject)
        throw GeexEngineException("D3D creation failed");

    //FIXME: make configurable?
    memset(&presentationParamenters, 0, sizeof(presentationParamenters));
    presentationParamenters.BackBufferWidth = width;
    presentationParamenters.BackBufferHeight = height;
    presentationParamenters.BackBufferFormat = D3DFMT_A8R8G8B8;
    presentationParamenters.BackBufferCount = 1;
    presentationParamenters.hDeviceWindow = window;
    presentationParamenters.Windowed = true;
    presentationParamenters.Flags = 0;
    presentationParamenters.FullScreen_RefreshRateInHz = 0;
    presentationParamenters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    
    presentationParamenters.EnableAutoDepthStencil = true;
    presentationParamenters.AutoDepthStencilFormat = D3DFMT_D24S8;
    //presentationParamenters.AutoDepthStencilFormat = D3DFMT_D16;

    //discard? flip? whatever?
    presentationParamenters.SwapEffect = D3DSWAPEFFECT_DISCARD;

    //deactivate aa for now
    presentationParamenters.MultiSampleType = D3DMULTISAMPLE_NONE;
    presentationParamenters.MultiSampleQuality = 0;

    if(FAILED(d3dObject->CreateDevice(D3DADAPTER_DEFAULT,
                                      D3DDEVTYPE_HAL,
                                      window,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
                                      &presentationParamenters,
                                      &d3dDevice)))
        throw GeexEngineException("D3D device creation failed");

    resourceFactory = new DirectXGraphicsResourceFactory(this->d3dDevice);
}

DirectXRenderer::~DirectXRenderer()
{
    if(resourceFactory)
    {
        delete resourceFactory;
        resourceFactory = NULL;
    }

    if(d3dDevice)
    {
        d3dDevice->Release();
        d3dDevice = NULL;
    }

    if(d3dObject)
    {
        d3dObject->Release();
        d3dObject = NULL;
    }
}

void DirectXRenderer::Resize(int newWidth, int newHeight)
{
    Renderer::Resize(newWidth, newHeight);

    presentationParamenters.BackBufferWidth = newWidth;
    presentationParamenters.BackBufferHeight = newHeight;

    OnDeviceLost();
    d3dDevice->Reset(&presentationParamenters);
    OnDeviceReset();
}

void DirectXRenderer::ToggleFullscreen()
{
    Renderer::ToggleFullscreen();

    presentationParamenters.Windowed = !isFullscreen;
    if(presentationParamenters.Windowed)
        presentationParamenters.FullScreen_RefreshRateInHz = 0;
    else
    {
        presentationParamenters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        GetWindowRect(presentationParamenters.hDeviceWindow, &oldWindowRect);			//save old window position
        ShowCursor(false);
    }

    OnDeviceLost();
    d3dDevice->Reset(&presentationParamenters);
    OnDeviceReset();

    //restore old window position if necessary
    if(presentationParamenters.Windowed)
    {
        SetWindowPos(presentationParamenters.hDeviceWindow,
                     NULL,
                     oldWindowRect.left,
                     oldWindowRect.top,
                     oldWindowRect.right - oldWindowRect.left,
                     oldWindowRect.bottom - oldWindowRect.top,
                     SWP_NOZORDER | SWP_DRAWFRAME | SWP_SHOWWINDOW
                     );
        ShowCursor(true);
    }
}

bool DirectXRenderer::BeginScene()
{
    if(!CheckCooperateLevel())
        return false;

    if(FAILED(d3dDevice->BeginScene()))
        throw GeexEngineException("D3D BeginScene failed");

    return true;
}

void DirectXRenderer::EndScene()
{
    if(FAILED(d3dDevice->EndScene()))
        throw GeexEngineException("D3D EndScene failed");
}

void DirectXRenderer::ClearBackBuffer()
{
    if(!CheckCooperateLevel())
        return;

    HRESULT result = d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(backgroundColor.R(), backgroundColor.G(), backgroundColor.B(), backgroundColor.A()), 1.0f, 0);
    if(FAILED(result))
        throw GeexEngineException("BackBuffer clearance failed");
}

void DirectXRenderer::ClearDepthBuffer()
{
    if(!CheckCooperateLevel())
        return;

    if(FAILED(d3dDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(backgroundColor.R(), backgroundColor.G(), backgroundColor.B(), backgroundColor.A()), 1.0f, 0)))
        throw GeexEngineException("Z-Buffer clearance failed");
}

void DirectXRenderer::ClearStencilBuffer()
{
    if(!CheckCooperateLevel())
        return;

    if(FAILED(d3dDevice->SetRenderState(D3DRS_STENCILMASK, ~0)))
        throw GeexEngineException("Setting of stencilmask in D3D-Device failed during clearance of stencil buffer");

    if(FAILED(d3dDevice->Clear(0, 0, D3DCLEAR_STENCIL, D3DCOLOR_COLORVALUE(backgroundColor.R(), backgroundColor.G(), backgroundColor.B(), backgroundColor.A()), 1.0f, 0)))
        throw GeexEngineException("StencilBuffer clearance failed");
}

void DirectXRenderer::ClearBuffers()
{
    if(!CheckCooperateLevel())
        return;

    //FIXME: what does this do? necessary?
    //if(FAILED(d3dDevice->SetRenderState(D3DRS_STENCILMASK, ~0)))
    //    throw GeexEngineException("Setting of stencilmask in D3D-Device failed during clearance of stencil buffer");

    if(FAILED(d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(backgroundColor.R(), backgroundColor.G(), backgroundColor.B(), backgroundColor.A()), 1.0f, 0)))
        throw GeexEngineException("Buffer clearance failed");
}

void DirectXRenderer::DrawPrimitive(PrimitiveType primitiveType, unsigned int startVertex, size_t primitiveCount)
{
    HRESULT res = d3dDevice->DrawPrimitive(GetD3DPrimitiveType(primitiveType), startVertex, primitiveCount);
    if(FAILED(res))
        throw GeexEngineException("Drawing primtives failed");
}

void DirectXRenderer::DrawIndexedPrimitive(IndexElementType indexElementType, PrimitiveType primitiveType, unsigned int startIndex, unsigned int vertexCountInBuffer, size_t primitiveCount)
{
    HRESULT res = d3dDevice->DrawIndexedPrimitive(GetD3DPrimitiveType(primitiveType), 0, 0, vertexCountInBuffer, startIndex, primitiveCount);
    if(FAILED(res))
        throw GeexEngineException("Drawing of indexed primtives failed");
}

void DirectXRenderer::SwapBuffers()
{
    if(!CheckCooperateLevel())
        return;

    HRESULT res = d3dDevice->Present(0, 0, 0, 0);
    if(res != D3DERR_DEVICELOST && FAILED(res))
        throw GeexEngineException("Error while presenting BackBuffer");
}

void DirectXRenderer::UpdateCamera(ICamera* camera)
{
    throw new GeexEngineException("Not implemented");
}

void DirectXRenderer::OnDeviceLost()
{
    DirectXResettableResource::NotifyDeviceLost();
}

void DirectXRenderer::OnDeviceReset()
{
    //TODO: Reset matrices etc.
    D3DVIEWPORT9 vp;
    vp.Height = this->curHeight;
    vp.Width = this->curWidth;
    vp.X = 0;
    vp.Y = 0;
    vp.MinZ = 0.0f;
    vp.MaxZ = 0.0f;
    d3dDevice->SetViewport(&vp);

    DirectXResettableResource::NotifyDeviceReset();
}

bool DirectXRenderer::CheckCooperateLevel()
{
    switch(d3dDevice->TestCooperativeLevel())
    {
    case D3DERR_DEVICELOST:
        if(!deviceIsLost)
        {
            deviceIsLost = true;
            OnDeviceLost();
        }
        return false;

    case D3DERR_DEVICENOTRESET:
        HRESULT result = d3dDevice->Reset(&presentationParamenters);
        if(FAILED(result))
            throw new GeexEngineException("Resetting the D3D Device failed");

        OnDeviceReset();
        deviceIsLost = false;
        return true;
    }

    return true;
}
