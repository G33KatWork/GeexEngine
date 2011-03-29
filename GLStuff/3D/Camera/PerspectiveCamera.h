#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include <3D/ICamera.h>
#include <Math/Vector3.h>

class PerspectiveCamera : public ICamera
{
protected:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

	//matrix for camera rotations
	Matrix4 rotationMatrix;

	//projection matrix parameters
	float fov;
	float aspect;
	float near1;
	float far1;

	//camera rotation
	float pitch;	//y-axis
	float yaw;		//y-axis

	//camera movement
	Vector3 forward;
	Vector3 strafeRight;

	//view matrix parameters
	const Vector3 defaultView;
	const Vector3 defaultUp;
	Vector3 eye;
	Vector3 view;
	Vector3 up;

	void recalculateProjectionMatrix();

public:
	PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
		:
		projectionMatrix(Matrix4::Identity()),
		viewMatrix(Matrix4::Identity()),
		rotationMatrix(Matrix4::Identity()),
		fov(fieldOfView),
		aspect(aspectRatio),
		near1(nearPlane),
		far1(farPlane),
		pitch(0),
		defaultView(Vector3(0,0,1)),
		defaultUp(Vector3(0,1,0)),
		eye(Vector3(0,0,0)),
		view(Vector3(0,0,1)),
		up(Vector3(0,1,0)),
		forward(Vector3(0,0,1)),
		strafeRight(Vector3(1,0,0))
	{
		this->recalculateProjectionMatrix();
		this->Update();
	}

	virtual ~PerspectiveCamera() {}

	float GetFieldOfView() const { return fov; }
	float GetAspectRatio() const { return aspect; }
	float GetNearPlane() const { return near1; }
	float GetFarPlane() const { return far1; }

	void SetFieldOfView(float newFieldOfView)
	{
		fov = newFieldOfView;
		this->recalculateProjectionMatrix();
	}

	void SetAspectRatio(float newAspectRatio)
	{
		aspect = newAspectRatio;
		this->recalculateProjectionMatrix();
	}

	void SetNearPlane(float newNearPlane)
	{
		near1 = newNearPlane;
		this->recalculateProjectionMatrix();
	}

	void SetFarPlane(float newFarPlane)
	{
		far1 = newFarPlane;
		this->recalculateProjectionMatrix();
	}

	/*Vector3& GetPositon() { return this->position; }
	Vector3& GetLookAt() { return this->lookAt; }
	Vector3& GetUp() { return this->up; }

	void Look(Vector3& target) { this->lookAt = target; }
	void MoveTo(Vector3& newPosition) { this->position = newPosition; }
	void MoveBy(Vector3& deltaPosition) { this->position += deltaPosition; }*/

	void SetPositionAndView(const Vector3& position, float pitch, float yaw);

	void Pitch(float theta);
	void Yaw(float theta);

	virtual void Update();

	virtual const Matrix4& GetProjectionMatrix() const { return this->projectionMatrix; }
	virtual const Matrix4& GetViewMatrix() const { return this->viewMatrix; }
};

#endif
