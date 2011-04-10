#include "TestApplication.h"

#include <Platform/Windows/Win32Window.h>
#include <3D/Rendering/OpenGL/WGLRenderer.h>
#include <Timing/Windows/WindowsTiming.h>
#include <Common/GeexEngineException.h>

#include <3D/Rendering/OpenGL/OpenGLVertexBuffer.h>

OpenGLVertexBuffer *buf;

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

struct GLVERTEX {float x, y, z; float r, g, b;};

bool TestApplication::OnInitialize()
{
    if(glewInit() != GLEW_OK)
        throw new GeexEngineException("GLEW initialization failed");

    world = Matrix4::Identity();
    projection = Matrix4::CreatePerspectiveLeftHanded(45.0f * 3.14f/180.0f, (float)this->window->GetWidth() / (float)this->window->GetHeight(), 0.1f, 100.0f);
    view = Matrix4::Identity();


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(projection[0]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    struct GLVERTEX vertices[] =
    {
        { -1.0f,  1.0f, 0.f,    0.0f, 0.0f, 1.0f, },
        {  1.0f,  1.0f, 0.f,    0.0f, 1.0f, 0.0f, },
        { -1.0f, -1.0f, 0.f,    1.0f, 0.0f, 0.0f, },
    };

    VertexBufferFormat format = VertexBufferFormat();
    size_t offset = 0;
    format.AddElement(offset, 3, GX_VB_ELEMENT_USAGE_POSITION, GX_VB_ELEMENT_TYPE_FLOAT);
    offset += VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT) * 3;
    format.AddElement(offset, 3, GX_VB_ELEMENT_USAGE_COLOR, GX_VB_ELEMENT_TYPE_FLOAT);

    buf = new OpenGLVertexBuffer(3, format);
    buf->SetData(vertices);

    renderer->SetBackgroundColor(Color(0.4f, 0.8f, 0.9f, 1.0f));

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

    Matrix4 rotation = Matrix4::Identity();
    rotation = Matrix4::Rotate(rotrightleft, Vector3(0.0f, 1.0f, 0.0f));
    rotation = rotation * Matrix4::Rotate(rotupdown, Vector3(1.0f, 0.0f, 0.0f));

    Matrix4 translation = Matrix4::Identity();
    translation = Matrix4::Translate(lr, ud, zoom);

    world = rotation * translation;

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((view * world)[0]);

    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,3.0f);*/

    if(renderer->BeginScene())
    {
        buf->Activate();
        renderer->DrawPrimitive(0, 1, PRIMTYPE_TRIANGLESTRIP);
        buf->Deactivate();

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
    return new WGLRenderer(((Win32Window*)forWindow)->GetWindowHandle(), forWindow->GetWidth(), forWindow->GetHeight());
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
