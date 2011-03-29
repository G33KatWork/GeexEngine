#ifndef _INPUTDEVICE_H_
#define _INPUTDEVICE_H_

class InputDevice
{
private:
public:
	InputDevice() {}
	virtual ~InputDevice() {}

	virtual void Create() = 0;
	virtual void Destroy() = 0;
	virtual void Update() = 0;
};

#endif
