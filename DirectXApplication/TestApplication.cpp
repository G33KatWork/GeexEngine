#include "TestApplication.h"

#include <Platform/Windows/Win32Window.h>
#include <3D/Rendering/DirectX/DirectXRenderer.h>
#include <Timing/Windows/WindowsTiming.h>

TestApplication::TestApplication()
    : Application()
{
    din = NULL;
    mouse = NULL;
    keyboard = NULL;

    buf = NULL;
    index = NULL;
    effect = NULL;

    lr = 0.0f;
    ud = 0.0f;
    zoom = 3.0f;
    rotrightleft = 0.0f;
    rotupdown = 0.0f;
}

bool TestApplication::OnInitialize()
{
    world = Matrix4::Identity();
    projection = Matrix4::CreatePerspectiveLeftHanded(45.0f * 3.14f/180.0f, (float)this->window->GetWidth() / (float)this->window->GetHeight(), 0.1f, 100.0f);
    view = Matrix4::Identity();

    effect = renderer->GetGraphicsResourceFactory()->CreateEffectFromFile("effect.fx");
    effect->SetTechniqueByName("hlsl");

    struct D3DVERTEX vertices[] =
    {
        { -1.0f,-1.0f,-1.0f,    0.0f, 0.0f, 1.0f },
        { -1.0f, 1.0f,-1.0f,    0.0f, 1.0f, 0.0f },
        {  1.0f, 1.0f,-1.0f,    1.0f, 0.0f, 0.0f },
        {  1.0f,-1.0f,-1.0f,    0.0f, 0.0f, 1.0f },
        { -1.0f,-1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
        {  1.0f,-1.0f, 1.0f,    1.0f, 0.0f, 0.0f },
        {  1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },
        { -1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f }
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
    format.AddElement(offset, 3, GX_VB_ELEMENT_USAGE_POSITION, GX_VB_ELEMENT_TYPE_FLOAT);
    offset += VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT) * 3;
    format.AddElement(offset, 3, GX_VB_ELEMENT_USAGE_COLOR, GX_VB_ELEMENT_TYPE_FLOAT);

    buf = renderer->GetGraphicsResourceFactory()->CreateVertexBuffer(8, format);
    buf->SetData(vertices);

    index = renderer->GetGraphicsResourceFactory()->CreateIndexBuffer(36, GX_IB_ELEMENT_TYPE_UINT16);
    index->SetData(indices);
    
    return true;
}

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

    Matrix4 rotation = Matrix4::Identity();
    rotation = Matrix4::Rotate(rotrightleft, Vector3(0.0f, 1.0f, 0.0f));
    rotation = rotation * Matrix4::Rotate(rotupdown, Vector3(1.0f, 0.0f, 0.0f));

    Matrix4 translation = Matrix4::Identity();
    translation = Matrix4::Translate(lr, ud, zoom);

    world = rotation * translation;

    effect->SetMatrix("worldViewProjection", world*view*projection);

    if(renderer->BeginScene())
    {
        buf->Activate();
        index->Activate();

        effect->Begin();

        while(effect->ExecutePass())
            renderer->DrawIndexedPrimitive(GX_IB_ELEMENT_TYPE_UINT16, PRIMTYPE_TRIANGLELIST, 0, 12);

        effect->End();

        index->Deactivate();
        buf->Deactivate();

        renderer->EndScene(); 
    }

    renderer->SwapBuffers();
}

void TestApplication::OnTerminate()
{
    if(effect)
    {
        delete effect;
        effect = NULL;
    }

    if(buf)
    {
        delete buf;
        buf = NULL;
    }

    if(index)
    {
        delete index;
        index = NULL;
    }

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
