/*
 *  Application.h
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <3D/Rendering/Renderer.h>
#include <Platform/Window.h>
#include <Timing/TimingInformation.h>

class Application
{
protected:
	Renderer* renderer;
	Window* window;
	TimingInformation* timer;

	bool running;

public:
    virtual ~Application();

    virtual bool OnPrecreate();
    virtual bool OnInitialize();
    virtual void OnTerminate();
    virtual void OnMove(int newX, int newY);
    virtual void OnResize(int newWidth, int newHeight);
    
	virtual void OnUpdate();
	virtual void OnRedraw();

    virtual int Main (int iQuantity, char** apcArgument);

	virtual void ToggleFullscreen() { renderer->ToggleFullscreen(); }
	virtual void Resize(int width, int height) { window->Resize(width, height); renderer->Resize(width, height); }
	virtual void Move(int x, int y) { window->Move(x, y); }
	virtual void Terminate() { running = false; }

    //Will be set in main() function of application with concrete instance
    static Application* TheApplication;

protected:
    Application();

	virtual Renderer* CreateRenderer(Window* forWindow) = 0;
	virtual Window* CreateRenderWindow() = 0;
	virtual TimingInformation* CreateTimer() = 0;
	virtual void CreateInputDevices(Window* forWindow) = 0;
};

#endif
