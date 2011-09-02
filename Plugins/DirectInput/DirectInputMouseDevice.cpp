#include "DirectInputMouseInputDevice.h"

DirectInputMouseInputDevice::DirectInputMouseInputDevice(LPDIRECTINPUT8 directInput, HWND windowHandle)
	: MouseInputDevice(),
	di(directInput),
	window(windowHandle)
{
	memset(&mouseState, 0, sizeof(DIMOUSESTATE2));
	mouseDevice = NULL;
	memset(&cursorPos, 0, sizeof(POINT));
}

DirectInputMouseInputDevice::~DirectInputMouseInputDevice()
{
	Destroy();
}

void DirectInputMouseInputDevice::Create()
{
	if(!di)
		return;	//FIXME: throw exception

	Destroy();

	if(FAILED(di->CreateDevice(GUID_SysMouse, &mouseDevice, NULL)))
		return;	//FIXME: throw exception

	if(FAILED(mouseDevice->SetDataFormat(&c_dfDIMouse2)))
		return;	//FIXME: throw exception

	if(FAILED(mouseDevice->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return; //FIXME: throw exception;

	if(FAILED(mouseDevice->Acquire()))
		return; //FIXME: throw exception;
}

void DirectInputMouseInputDevice::Destroy()
{
	if(mouseDevice)
	{
		mouseDevice->Unacquire();
		mouseDevice->Release();
		mouseDevice = NULL;
	}
}

void DirectInputMouseInputDevice::Update()
{
	if(!mouseDevice)
		return;

	HRESULT hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);
	if(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	{
		if(FAILED(mouseDevice->Acquire()))
		{
			return; //FIXME: throw error?
		}
	}

	GetCursorPos(&cursorPos);
	ScreenToClient(window, &cursorPos);
}

bool DirectInputMouseInputDevice::GetButtonState(KeyCode key)
{
	switch(key)
	{
	case KEY_LBUTTON:
		return (mouseState.rgbButtons[0] & 0x80) != 0;
	case KEY_RBUTTON:
		return (mouseState.rgbButtons[1] & 0x80) != 0;
	case KEY_MBUTTON:
		return (mouseState.rgbButtons[2] & 0x80) != 0;
	case KEY_XBUTTON1:
		return (mouseState.rgbButtons[3] & 0x80) != 0;
	case KEY_XBUTTON2:
		return (mouseState.rgbButtons[4] & 0x80) != 0;
	default:
		return false;
	}
}
