#ifndef _ICAMERA_H_
#define _ICAMERA_H_

#include <Math/Matrix4.h>

class ICamera
{
public:
	virtual void Update() = 0;

	virtual const Matrix4& GetViewMatrix() const = 0;
	virtual const Matrix4& GetProjectionMatrix() const = 0;
};

#endif
