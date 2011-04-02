#include <Application.h>
#include <cassert>
#include <cstdio>
#include <stddef.h>

Application* Application::TheApplication = NULL;

Application::Application()
{
    window = NULL;
    renderer = NULL;
    timer = NULL;
    running = true;
}

Application::~Application()
{
}

int Application::Main(int iQuantity, char** apcArgument)
{
    assert(Application::TheApplication);
    if(!Application::TheApplication)
        return -1;

    if(!OnPrecreate())
        return -2;


    window = this->CreateRenderWindow();
    window->Create();
    renderer = this->CreateRenderer(window);
    this->CreateInputDevices(window);
    timer = this->CreateTimer();

    if(!OnInitialize())
        return -4;

    window->Show();

    while (this->running)
    {
        if(!window->HandleEvents())
            break;

        timer->Update();

        //TODO: Call OnRedraw() at a fixed rate (i.e. 60 times per second or so). VSync?
        OnUpdate();
        OnRedraw();
    }

    OnTerminate();

    if(timer)
    {
        delete timer;
        timer = NULL;
    }

    if(renderer)
    {
        delete renderer;
        renderer = NULL;
    }

    if(window)
    {
        window->Destroy();
        delete window;
        window = NULL;
    }

    return 0;
};

bool Application::OnPrecreate()
{
    return true;
}

bool Application::OnInitialize()
{
    return true;
}

void Application::OnTerminate()
{
    renderer = NULL;
}

void Application::OnMove(int newX, int newY)
{
}

void Application::OnResize(int newWidth, int newHeight)
{
    if(renderer && newWidth > 0 && newHeight > 0)
        renderer->Resize(newWidth, newHeight);
}

void Application::OnUpdate() {}

void Application::OnRedraw() {}
