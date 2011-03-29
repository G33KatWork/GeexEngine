#include <3D/Rendering/OpenGL/WGLRenderer.h>
#include <Common/GeexEngineException.h>

WGLRenderer::WGLRenderer(HWND window, int width, int height)
    : OpenGLRenderer(width, height)
{
    deviceContext = NULL;
    renderingContext = NULL;
	pixelFormat = 0;

    windowHandle = window;

    if(!(deviceContext = GetDC(windowHandle)))
        throw GeexEngineException("Failed to acquire device context");

	//FIXME: make configurable?
    static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
    {
        sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
        1,											// Version Number
        PFD_DRAW_TO_WINDOW |						// Format Must Support Window
        PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
        PFD_DOUBLEBUFFER,							// Must Support Double Buffering
        PFD_TYPE_RGBA,								// Request An RGBA Format
        24,											// Select Our Color Depth
        0, 0, 0, 0, 0, 0,							// Color Bits Ignored
        0,											// No Alpha Buffer
        0,											// Shift Bit Ignored
        0,											// No Accumulation Buffer
        0, 0, 0, 0,									// Accumulation Bits Ignored
        16,											// 16Bit Z-Buffer (Depth Buffer)  
        0,											// No Stencil Buffer
        0,											// No Auxiliary Buffer
        PFD_MAIN_PLANE,								// Main Drawing Layer
        0,											// Reserved
        0, 0, 0										// Layer Masks Ignored
    };

	if (!(pixelFormat=ChoosePixelFormat(deviceContext,&pfd)))
        throw GeexEngineException("Failed to choose a pixel format");

	if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
        throw GeexEngineException("Failed to set pixel format");

    if (!(renderingContext = wglCreateContext(deviceContext)))
        throw GeexEngineException("Failed to create rendering context");

    if (!wglMakeCurrent(deviceContext, renderingContext))
        throw GeexEngineException("Failed to set current rendering context");
}

WGLRenderer::~WGLRenderer()
{
	if(renderingContext != NULL)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(renderingContext);
        renderingContext = NULL;
    }

    if(deviceContext != NULL)
    {
        ReleaseDC(windowHandle, deviceContext);
        deviceContext = NULL;
    }
}

void WGLRenderer::ToggleFullscreen()
{
	Renderer::ToggleFullscreen();

    if(!isFullscreen)	//comming out of fullscreen
	{
		ChangeDisplaySettings(NULL,0);
	}
    else				//going into fullscreen
    {
		GetWindowRect(windowHandle, &oldWindowRect);	//save old window position

		//switch resolution
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = this->curWidth;
		dmScreenSettings.dmPelsHeight = this->curHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(windowHandle, "Error switching to fullscreen with given resolution. Staying in windowed mode.", "Error switching to fullscreen", MB_OK | MB_ICONEXCLAMATION);
			isFullscreen = false;
			return;
		}

		//remove window border and move it into position
		SetWindowLong(windowHandle, GWL_STYLE, WS_POPUP);
		SetWindowPos(windowHandle,
					 NULL,
					 0,
					 0,
					 this->curWidth,
					 this->curHeight,
					 SWP_NOZORDER | SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_SHOWWINDOW
					 );

        ShowCursor(false);
    }

	//restore old window position is necessary
    if(!isFullscreen)
    {
		SetWindowLong(windowHandle, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
		SetWindowPos(windowHandle,
                     NULL,
                     oldWindowRect.left,
                     oldWindowRect.top,
                     oldWindowRect.right - oldWindowRect.left,
                     oldWindowRect.bottom - oldWindowRect.top,
                     SWP_NOZORDER | SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_SHOWWINDOW
                     );
        ShowCursor(true);
    }
}

void WGLRenderer::SwapBuffers()
{
    ::SwapBuffers(deviceContext);
}
