#ifndef _ORTHOCAMERA_H_
#define _ORTHOCAMERA_H_

#include <3D/ICamera.h>
#include <Math/Vector2.h>

class OrthographicCamera : public ICamera
{
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

	Point position;
	int width;
	int height;
	float near;
	float far;
	float zoom;

public:
	OrthographicCamera(Point position, float zoom, int width, int height, float near, float far)
		: position(position),
		  zoom(zoom),
		  width(width),
		  height(height),
		  near(near),
		  far(far),
		  viewMatrix(Matrix4::Identity()),
		  projectionMatrix(Matrix4::Zero())
	{
		this->Update();
	}

	virtual ~OrthographicCamera() {}

	/*virtual void SetPosition(Point newPosition, float newZoom)
	{
		position = newPosition;
		zoom = zoom;
	}*/

	virtual void Update();

	virtual const Matrix4& GetProjectionMatrix() const { return this->projectionMatrix; }
	virtual const Matrix4& GetViewMatrix() const { return this->viewMatrix; }
};

#endif
