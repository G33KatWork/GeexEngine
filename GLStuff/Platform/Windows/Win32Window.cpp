#include <Platform/Windows/Win32Window.h>
#include <Platform/Application.h>

LRESULT CALLBACK WinProc (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    Application* app = Application::TheApplication;
    if (!app)
        return DefWindowProc(hWnd, uiMsg, wParam, lParam);

    switch(uiMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            app->OnRedraw();
            EndPaint(hWnd, &ps);
            return 0;
        }

        case WM_MOVE:
        {
            int xPos = (int)LOWORD(lParam);
            int yPos = (int)HIWORD(lParam);
            app->OnMove(xPos, yPos);
            return 0;
        }

        case WM_SIZE:
        {
            int newWidth = (int)LOWORD(lParam);
            int newHeight = (int)HIWORD(lParam);
            app->OnResize(newWidth, newHeight);
            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

void Win32Window::Create()
{
    HINSTANCE hInst = GetModuleHandle(NULL);

    WNDCLASS wc;
    wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc		= (WNDPROC) WinProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInst;
    wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground	= NULL;
    wc.lpszMenuName		= NULL;
    wc.lpszClassName	= "GeekD3DWindow";

    if(!RegisterClass(&wc))
        return;	//FIXME: Handle error

    RECT windowRect;
    windowRect.bottom = this->windowHeight - 1;
    windowRect.top = this->y;
    windowRect.left = this->x;
    windowRect.right = this->windowWidth - 1;
    AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

    hWnd = CreateWindow(
        "GeekD3DWindow",
        this->windowTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        this->x,
        this->y,
        windowRect.right - windowRect.left + 1,
        windowRect.bottom - windowRect.top + 1,
        0,
        0,
        hInst,
        NULL);
}

void Win32Window::Destroy()
{
    if(hWnd)
    {
        DestroyWindow(hWnd);
        hWnd = NULL;
    }

    UnregisterClass("GeekD3DWindow", GetModuleHandle(NULL));
}

void Win32Window::Resize(int newWidth, int newHeight)
{
    this->windowWidth = newWidth;
    this->windowHeight = newHeight;
    UpdateWindowSizeAndPosition();
}

void Win32Window::Move(int xPos, int yPos)
{
    this->x = xPos;
    this->y = yPos;
    UpdateWindowSizeAndPosition();
}

void Win32Window::Show()
{
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

void Win32Window::Hide()
{
    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);
}

bool Win32Window::HandleEvents()
{
    MSG kMsg;
    while(PeekMessage(&kMsg,0,0,0,PM_REMOVE))
    {
        if (kMsg.message == WM_QUIT)
            return false;

        TranslateMessage(&kMsg);
        DispatchMessage(&kMsg);
    }
    
    return true;
}

void Win32Window::UpdateWindowSizeAndPosition()
{
    RECT windowRect;
    windowRect.bottom = this->windowHeight - 1;
    windowRect.top = this->y;
    windowRect.left = this->x;
    windowRect.right = this->windowWidth - 1;
    AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

    SetWindowPos(hWnd, NULL, this->x, this->y, windowRect.right - windowRect.left + 1, windowRect.bottom - windowRect.top + 1, SWP_SHOWWINDOW);
}
