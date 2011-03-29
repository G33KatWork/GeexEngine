#ifndef _WIN32_WINDOW_H_
#define _WIN32_WINDOW_H_

#include <Platform/Window.h>
#include <Windows.h>

class Win32Window : public Window
{
private:
	HWND hWnd;

public:
	Win32Window(const char* title, int xPos, int yPos, int width, int height)
		: Window(title, xPos, yPos, width, height)
	{
		hWnd = NULL;
	}
    
	virtual ~Win32Window() {}

    virtual void Create();
	virtual void Destroy();

	virtual void Resize(int newWidth, int newHeight);
	virtual void Move(int xPos, int yPos);

	virtual void Show();
	virtual void Hide();

	virtual bool HandleEvents();

	HWND GetWindowHandle() { return hWnd; }

private:
	void UpdateWindowSizeAndPosition();
};

#endif
