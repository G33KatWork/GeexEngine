#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <Common/GeexEngineExports.h>

class GEEXENGINE_API Window
{
public:
	virtual ~Window() {};

    virtual void Create() = 0;
	virtual void Destroy() = 0;

	virtual void Resize(int newWidth, int newHeight) = 0;
	virtual void Move(int xPos, int yPos) = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual bool HandleEvents() = 0;

	int GetHeight() { return windowHeight; }
	int GetWidth() { return windowWidth; }

protected:
    Window(const char* title, int xPos, int yPos, int width, int height)
	{
		windowTitle = title;
		x = xPos;
		y = yPos;
		windowWidth = width;
		windowHeight = height;
	}

    int x, y, windowWidth, windowHeight;
    const char* windowTitle;
};

#endif
