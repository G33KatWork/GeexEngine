/*
 *  Application.h
 *  Physics
 *
 *  Created by Andreas Galauner on 06.05.10.
 *  Copyright 2010 none. All rights reserved.
 *
 */

#ifndef _GX_APPLICATION_H_
#define _GX_APPLICATION_H_

#include <Common/GeexEngineExports.h>

#include <Plugins/PluginManager.h>
#include <3D/Rendering/Renderer.h>
#include <Platform/Window.h>
#include <Timing/TimingInformation.h>
#include <Input/InputManager.h>
#include <Resources/ResourceManager.h>

class GEEXENGINE_API Application
{
protected:
	Renderer* renderer;
	Window* window;
	TimingInformation* timer;
    InputManager* input;
    ResourceManager* resourceManager;
    PluginManager* pluginManager;

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
	virtual InputManager* CreateInputDevices(Window* forWindow) = 0;

    //FIXME: Implement this. To be implemented by an application which delivers resolution,
    //       window position and various rendering parameters to the engine with this method
    //virtual DisplayParameters GetDesiredDisplayParameters() = 0;
};

#endif
