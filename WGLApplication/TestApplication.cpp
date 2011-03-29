#include "TestApplication.h"

#include <Platform/Windows/Win32Window.h>
#include <Rendering/OpenGL/WGLRenderer.h>
#include <Timing/Windows/WindowsTiming.h>

TestApplication::TestApplication()
    : Application()
{
    din = NULL;
    mouse = NULL;
    keyboard = NULL;
    camera = NULL;
}

bool TestApplication::OnInitialize()
{
    renderer->SetBackgroundColor(Color(0.4f, 0.8f, 0.9f, 1.0f));
    //camera = new PerspectiveCamera(45.0f, (float)renderer->GetWidth() / (float)renderer->GetHeight(), 1.0f, 100.0f, Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
    camera = new PerspectiveCamera(45.0f, (float)renderer->GetWidth() / (float)renderer->GetHeight(), 1.0f, 100.0f);
    camera->SetPositionAndView(Vector3(0,0,10), 0, 0);
    renderer->UpdateCamera(camera);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(45.0f, renderer->GetWidth() / renderer->GetHeight(), 1.0f, 100.0f);

    //gluLookAt(0.0, 0.0, 10.0, /* eye point */
    //    0.0, 0.0, 0.0,  /* reference point */
    //    0.0, 1.0, 0.0); /* up vector */

    /*float x[16];
    int i;

    glGetFloatv (GL_PROJECTION_MATRIX, (float*)x);
    printf("GL_PROJECTION_MATRIX:\n");
    for(i=0; i<4; i++) {
        printf("%f\t%f\t%f\t%f", x[i], x[i+4], x[i+8], x[i+12]);  
        printf("\n");
    }*/

    return true;
}

void TestApplication::OnUpdate()
{
    mouse->Update();
    keyboard->Update();

    /*unsigned long long l = timer->GetLastFrameDuration();
    float lastFrame = (float)l / 1000.0f;

    camera->Pitch(mouse->GetYDelta() / 10000.0f);
    camera->Yaw(-mouse->GetXDelta() / 10000.0f);*/

    if(keyboard->KeyPressed(KEY_KEY_F))
        this->ToggleFullscreen();

    if(keyboard->KeyPressed(KEY_ESCAPE))
        this->Terminate();

    camera->Update();
    renderer->UpdateCamera(camera);
}

void TestApplication::OnRedraw()
{
    renderer->ClearBuffers();

    if(/*renderer->BeginScene()*/true)
    {
        /* draw a triangle */
        glBegin(GL_TRIANGLES);

        /* red vertex */
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-2.0f, -1.0f, 0.0f);

        /* green vertex */
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 2.0f, 0.0f);

        /* blue vertex */
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(2.0f, -1.0f, 0.0f);

        glEnd();

        /*glColor3f(0.65f, 1.0f, 0.45f);
        glBegin(GL_TRIANGLES);
        {
            for(int x=-20; x<20; x++){
                for(int y=-20; y<20; y++){
                    float a = 1;
                    glVertex3f( .5+x*a+a*.95, y*a+a*.95, 0);
                    glVertex3f( .5+x*a, y*a+a*.95, 0);
                    glVertex3f( .5+x*a+a*.95, y*a, 0);
                    glVertex3f( .5+x*a+a*.95, y*a, 0);
                    glVertex3f( .5+x*a, y*a, 0);
                    glVertex3f( .5+x*a, y*a+a*.95, 0);
                }
            }
        }
        glEnd();*/
        //renderer->EndScene();
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
