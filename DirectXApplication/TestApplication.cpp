#include "TestApplication.h"

#include <Platform/Windows/Win32Window.h>
#include <3D/Rendering/DirectX/DirectXRenderer.h>
#include <Timing/Windows/WindowsTiming.h>

#include <stdexcept>

struct D3DVERTEX {float x, y, z, rhw; DWORD color;};

#include <3D/Rendering/DirectX/DirectXVertexBuffer.h>
#include <3D/Rendering/DirectX/DirectXEffect.h>

const char* effectSource = 
{
"struct VIn\n"
"{\n"
"    float4 position : POSITION;\n"
"    float4 color : COLOR;\n"
"};\n"
"    \n"
"struct VOut\n"
"{\n"
"    float4 position : SV_POSITION;\n"
"    float4 color : COLOR;\n"
"};\n"
"\n"
"struct POut\n"
"{\n"
"    float4 Color : COLOR0;\n"
"};\n"
"\n"
"\n"
"//float4x4 worldViewProjection;\n"
"\n"
"\n"
"VOut VShader(VIn vin)\n"
"{\n"
"    VOut output;\n"
"    \n"
"    output.position = vin.position;\n"
"    //output.position = mul(vin.position, worldViewProjection);\n"
"    output.color = vin.color;\n"
"    \n"
"    return output;\n"
"}\n"
"\n"
"POut PShader(VOut vout) : SV_TARGET\n"
"{\n"
"    POut pout;\n"
"    \n"
"    pout.Color = vout.color;\n"
"    return pout;\n"
"}\n"
"\n"
"\n"
"technique Simplest\n"
"{\n"
"    pass Pass0\n"
"    {        \n"
"        VertexShader = compile vs_2_0 VShader();\n"
"        PixelShader = compile ps_2_0 PShader();\n"
"    }\n"
"}\n"
};

DirectXEffect* effect;
DirectX9VertexBuffer *buf;

TestApplication::TestApplication()
    : Application()
{
    din = NULL;
    mouse = NULL;
    keyboard = NULL;
}
#include <iostream>
#include <d3dx9.h>
bool TestApplication::OnInitialize()
{
    //Effect::CreateFromSourceCode("effect.fx", renderer);
    effect = new DirectXEffect(((DirectXRenderer*)renderer)->GetDevice(), effectSource);

    struct D3DVERTEX vertices[] =
    {
        { 400.0f, 62.5f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    renderer->SetBackgroundColor(Color(0.4f, 0.8f, 0.9f, 1.0f));

    VertexBufferFormat format = VertexBufferFormat();
    size_t offset = 0;
    format.AddElement(offset, VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT4), GX_VB_ELEMENT_USAGE_POSITION, GX_VB_ELEMENT_TYPE_FLOAT4);
    offset += VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_FLOAT4);
    format.AddElement(offset, VertexElement::GetTypeSize(GX_VB_ELEMENT_TYPE_UBYTE4), GX_VB_ELEMENT_USAGE_COLOR, GX_VB_ELEMENT_TYPE_UBYTE4);
    
    std::cout << "size of struct: " << sizeof(D3DVERTEX) * 3 << std::endl;
    std::cout << "size of declaration: " << format.GetTotalVertexSize() * 3 << std::endl;

    buf = new DirectX9VertexBuffer(((DirectXRenderer*)renderer)->GetDevice(), 3, format);
    buf->SetData(&vertices);

    D3DXMATRIX a;
    D3DXMatrixIdentity(&a);
    //D3DXMatrixRotationX(&a, 45.0f * 3.14f / 180.0f);
    //D3DXMatrixPerspectiveFovRH(&a, 45.0f * 3.14f / 180.0f, 4.0f/3.0f, 100.0f, 0.0f);
    D3DXVECTOR3 eye, at, up;
    eye.x = eye.y = eye.z = 0.0f;
    at.x = at.y = at.z = 10.0f;
    up.x = 1.0f; up.y = 2.0f; up.z = 3.0f;

    D3DXMatrixLookAtRH(&a, &eye, &at, &up);
    std::cout << a(0, 0) << " " << a(0, 1) << " " << a(0, 2) << " " << a(0, 3) << std::endl;
    std::cout << a(1, 0) << " " << a(1, 1) << " " << a(1, 2) << " " << a(1, 3) << std::endl;
    std::cout << a(2, 0) << " " << a(2, 1) << " " << a(2, 2) << " " << a(2, 3) << std::endl;
    std::cout << a(3, 0) << " " << a(3, 1) << " " << a(3, 2) << " " << a(3, 3) << std::endl;

    Matrix4 m = Matrix4::Identity();
    //m = Matrix4::Rotate(45.0f * 3.14f / 180.0f, Vector3(1.0f, 0.0f, 0.0f));
    //m = Matrix4::CreatePerspectiveRightHanded(45.0f * 3.14f / 180.0f, 4.0f/3.0f, 100.0f, 0.0f);
    m = Matrix4::CreateLookAtRightHanded(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f), Vector3(1.0f, 2.0f, 3.0f));
    std::cout << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << " " << m(0, 3) << std::endl;
    std::cout << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << " " << m(1, 3) << std::endl;
    std::cout << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << " " << m(2, 3) << std::endl;
    std::cout << m(3, 0) << " " << m(3, 1) << " " << m(3, 2) << " " << m(3, 3) << std::endl;

    return true;
}

void TestApplication::OnUpdate()
{
    mouse->Update();
    keyboard->Update();

    if(keyboard->KeyPressed(KEY_KEY_F))
        this->ToggleFullscreen();

    if(keyboard->KeyPressed(KEY_ESCAPE))
        this->Terminate();
}

void TestApplication::OnRedraw()
{
    renderer->ClearBackBuffer();
    
    if(renderer->BeginScene())
    {
        buf->Activate();
        effect->SetTechniqueByName("Simplest");

        unsigned int numPasses = effect->Begin();
        for(unsigned int i = 0; i < numPasses; i++)
        {
            effect->BeginPass(i);
            ((DirectXRenderer*)renderer)->GetDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 1);
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
