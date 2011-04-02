#include "TestApplication.h"

#include <Platform/Windows/Win32Window.h>
#include <3D/Rendering/DirectX/DirectXRenderer.h>
#include <Timing/Windows/WindowsTiming.h>

#include <stdexcept>

#include <3D/Rendering/DirectX/DirectXVertexBuffer.h>
#include <3D/Rendering/DirectX/DirectXIndexBuffer.h>
#include <3D/Rendering/DirectX/DirectXEffect.h>
#include <3D/Rendering/DirectX/DirectXTexture.h>

DirectXEffect* effect;
DirectX9VertexBuffer *buf;
DirectX9IndexBuffer *indexBuf;
DirectXTexture *texture;

Matrix4 world;
Matrix4 projection;
Matrix4 view;

TestApplication::TestApplication()
    : Application()
{
    din = NULL;
    mouse = NULL;
    keyboard = NULL;
}
#include <iostream>
#include <d3dx9.h>

struct D3DVERTEX {float x, y, z, tu, tv;};

bool TestApplication::OnInitialize()
{
    world = Matrix4::Identity();
    projection = Matrix4::CreatePerspectiveLeftHanded(45.0f * 3.14f/180.0f, (float)this->window->GetWidth() / (float)this->window->GetWidth(), 0.1f, 100.0f);
    view = Matrix4::Identity();

    effect = new DirectXEffect(((DirectXRenderer*)renderer)->GetDevice(), "effect.fx", true);

    texture = new DirectXTexture(((DirectXRenderer*)renderer)->GetDevice(), "test.bmp");

    struct D3DVERTEX vertices[] =
    {
        {-1.0f,-1.0f,-1.0f,0.0f,1.0f},
        {-1.0f, 1.0f,-1.0f,0.0f,0.0f},
        { 1.0f, 1.0f,-1.0f,1.0f,0.0f},
        { 1.0f,-1.0f,-1.0f,1.0f,1.0f},
        {-1.0f,-1.0f, 1.0f,0.0f,0.0f},
        { 1.0f,-1.0f, 1.0f,0.0f,1.0f},
        { 1.0f, 1.0f, 1.0f,0.0f,0.0f},
        {-1.0f, 1.0f, 1.0f,0.0f,1.0f}
    };

    short indices[] = 
    {
        0,1,2, 2,3,0, 4,5,6,
        6,7,4, 0,3,5, 5,4,0,
        3,2,6, 6,5,3, 2,1,7,
        7,6,2, 1,0,4, 4,7,1
    };

    renderer->SetBackgroundColor(Color(0.4f, 0.8f, 0.9f, 1.0f));

    VertexBufferFormat format = VertexBufferFormat();
    size_t offset = 0;
    format.AddElement(offset, VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT3), GX_VB_ELEMENT_USAGE_POSITION, GX_VB_ELEMENT_TYPE_FLOAT3);
    offset += VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT3);
    format.AddElement(offset, VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT2), GX_VB_ELEMENT_USAGE_TEXTURE_COORDINATES, GX_VB_ELEMENT_TYPE_FLOAT2);
    
    std::cout << "size of struct: " << sizeof(D3DVERTEX) * 8 << std::endl;
    std::cout << "size of declaration: " << format.GetTotalVertexSize() * 8 << std::endl;

    buf = new DirectX9VertexBuffer(((DirectXRenderer*)renderer)->GetDevice(), 8, format);
    buf->SetData(&vertices);

    indexBuf = new DirectX9IndexBuffer(((DirectXRenderer*)renderer)->GetDevice(), 36, GX_IB_ELEMENT_TYPE_UINT16);
    indexBuf->SetData(&indices);

    D3DXMATRIX a;
    D3DXMatrixIdentity(&a);
    D3DXMatrixRotationZ(&a, 45.0f * 3.14f / 180.0f);
    D3DXMATRIX t;
    D3DXMatrixTranslation(&t, 1.0f, 2.0f, 3.0f);
    D3DXMatrixMultiply(&a, &a, &t);

    //D3DXMatrixPerspectiveFovLH(&a, 45.0f * 3.14f / 180.0f, 4.0f/3.0f, 100.0f, 0.0f);
    D3DXVECTOR3 eye, at, up;
    eye.x = eye.y = eye.z = 0.0f;
    at.x = at.y = at.z = 10.0f;
    up.x = 1.0f; up.y = 2.0f; up.z = 3.0f;

    //D3DXMatrixLookAtRH(&a, &eye, &at, &up);
    std::cout << a(0, 0) << " " << a(0, 1) << " " << a(0, 2) << " " << a(0, 3) << std::endl;
    std::cout << a(1, 0) << " " << a(1, 1) << " " << a(1, 2) << " " << a(1, 3) << std::endl;
    std::cout << a(2, 0) << " " << a(2, 1) << " " << a(2, 2) << " " << a(2, 3) << std::endl;
    std::cout << a(3, 0) << " " << a(3, 1) << " " << a(3, 2) << " " << a(3, 3) << std::endl;

    Matrix4 m = Matrix4::Identity();
    m = Matrix4::Rotate(45.0f * 3.14f / 180.0f, Vector3(0.0f, 0.0f, 1.0f));
    m = m * Matrix4::Translate(1.0f, 2.0f, 3.0f);
    //m = Matrix4::CreatePerspectiveLeftHanded(45.0f * 3.14f / 180.0f, 4.0f/3.0f, 100.0f, 0.0f);
    //m = Matrix4::CreateLookAtRightHanded(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 2.0f, 3.0f));
    std::cout << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << " " << m(0, 3) << std::endl;
    std::cout << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << " " << m(1, 3) << std::endl;
    std::cout << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << " " << m(2, 3) << std::endl;
    std::cout << m(3, 0) << " " << m(3, 1) << " " << m(3, 2) << " " << m(3, 3) << std::endl;

    return true;
}
float lr = 0.0f; //left right
float ud = 0.0f; //up down
float zoom = 3.0f;
float rotrightleft = 0.0f;
float rotupdown = 0.0f;

void TestApplication::OnUpdate()
{
    mouse->Update();
    keyboard->Update();

    if(keyboard->KeyPressed(KEY_KEY_F))
        this->ToggleFullscreen();

    if(keyboard->KeyPressed(KEY_KEY_D))
        lr+=.05f;
    if(keyboard->KeyPressed(KEY_KEY_A))
        lr-=.05f;

    if(keyboard->KeyPressed(KEY_KEY_W))
        ud+=.05f;
    if(keyboard->KeyPressed(KEY_KEY_S))
        ud-=.05f;

    if(keyboard->KeyPressed(KEY_KEY_X))
        zoom+=.05f;
    if(keyboard->KeyPressed(KEY_KEY_C))
        zoom-=.05f;

    if(keyboard->KeyPressed(KEY_LEFT))
        rotrightleft+=.05f;
    if(keyboard->KeyPressed(KEY_RIGHT))
        rotrightleft-=.05f;

    if(keyboard->KeyPressed(KEY_UP))
        rotupdown+=.05f;
    if(keyboard->KeyPressed(KEY_DOWN))
        rotupdown-=.05f;

    if(keyboard->KeyPressed(KEY_ESCAPE))
        this->Terminate();
}

void TestApplication::OnRedraw()
{
    renderer->ClearBuffers();
    
    if(renderer->BeginScene())
    {
        effect->SetTechniqueByName("Simplest");

        Matrix4 rotation = Matrix4::Identity();
        rotation = Matrix4::Rotate(rotrightleft, Vector3(0.0f, 1.0f, 0.0f));
        rotation = rotation * Matrix4::Rotate(rotupdown, Vector3(1.0f, 0.0f, 0.0f));

        Matrix4 translation = Matrix4::Identity();
        translation = Matrix4::Translate(lr, ud, zoom);

        world = rotation * translation;

        effect->SetMatrix("worldViewProjection", world*view*projection /*Matrix4::Identity()*/);
        effect->SetTexture("testTexture", texture);
        
        unsigned int numPasses = effect->Begin();
        for(unsigned int i = 0; i < numPasses; i++)
        {
            effect->BeginPass(i);

            buf->Activate();
            indexBuf->Activate();
            ((DirectXRenderer*)renderer)->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

            effect->EndPass();
        }
        effect->End();
        
        renderer->EndScene();
    }

    renderer->SwapBuffers();
}

void TestApplication::OnTerminate()
{
    if(mouse)
    {
        mouse->Destroy();
        delete mouse;
        mouse = NULL;
    }

    if(keyboard)
    {
        keyboard->Destroy();
        delete keyboard;
        keyboard = NULL;
    }

    if(din)
    {
        din->Release();
        din = NULL;
    }
}

Renderer* TestApplication::CreateRenderer(Window* forWindow)
{
    return new DirectXRenderer(((Win32Window*)forWindow)->GetWindowHandle(), forWindow->GetWidth(), forWindow->GetHeight());
}

Window* TestApplication::CreateRenderWindow()
{
    return (new Win32Window("GeexEngine Window", 0, 0, 640, 480));
}

TimingInformation* TestApplication::CreateTimer()
{
    return new WindowsTiming();
}

void TestApplication::CreateInputDevices(Window* forWindow)
{
    DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&din, NULL);

    mouse = new DirectInputMouseInputDevice(din, ((Win32Window*)forWindow)->GetWindowHandle());
    mouse->Create();

    keyboard = new DirectInputKeyboardInputDevice(din, ((Win32Window*)forWindow)->GetWindowHandle());
    keyboard->Create();
}

int main(int argc, char** argv)
{
    TestApplication* ta = new TestApplication();
    Application::TheApplication = ta;
    ta->Main(argc, argv);
}
