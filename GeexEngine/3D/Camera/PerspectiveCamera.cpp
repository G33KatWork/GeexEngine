#define _USE_MATH_DEFINES
#include <cmath>

#include <3D/PerspectiveCamera.h>
#include <Math/Quaternion.h>

#include <cstdio>

void PerspectiveCamera::recalculateProjectionMatrix()
{
	projectionMatrix = Matrix4::CreatePerspective(this->fov, this->aspect, this->near1, this->far1);

	/*printf("projectionMatrix:\n");
	for(int i=1; i<=16; i++) {
		printf("%f\t", projectionMatrix((i-1) / 4, (i-1) % 4));
		if(i % 4 == 0)
			printf("\n");
	}
	printf("\n");
	printf("\n");*/
}

void PerspectiveCamera::SetPositionAndView(const Vector3& position, float pitch, float yaw)
{
	eye = position;
	this->pitch = pitch * (float)M_PI/180;	//DEG2RAD
	this->yaw = yaw * (float)M_PI/180;

	this->Update();
}
#include <iostream>
void PerspectiveCamera::Pitch(float theta)
{
	pitch += theta;

	//clamp between 0 and 2*PI
	if (pitch > (float)2*M_PI) pitch -= (float)(2*M_PI);
	else if (pitch < 0.0f) pitch = (float)(2*M_PI + pitch);
}

void PerspectiveCamera::Yaw(float theta)
{
	yaw += theta;

	//clamp between 0 and 2*PI
	if (yaw > (float)2*M_PI) yaw -= (float)(2*M_PI);
	else if (yaw < 0.0f) yaw = (float)(2*M_PI + yaw);

	std::cout << "Yaw: " << yaw << std::endl;
}

void PerspectiveCamera::Update()
{
	//pitch = rotation on x-axis
	//this->rotationMatrix = Matrix4::Rotate(this->pitch, Vector3(1.0f, 0.0f, 0.0f));
	//this->rotationMatrix = this->rotationMatrix * Matrix4::Rotate(this->yaw, Vector3(0.0f, 1.0f, 0.0f));

	Quaternion qYaw = Quaternion::CreateFromAxisAngle(0.0f, 0.0f, 1.0f, this->yaw);
	Quaternion qPitch = Quaternion::CreateFromAxisAngle(1.0f, 0.0f, 0.0f, this->pitch);

	this->rotationMatrix = (qYaw * qPitch).CreateMatrix();

	//create new vectors
	this->view = this->defaultView * this->rotationMatrix;
	this->up = this->defaultUp * this->rotationMatrix;

	//move camera
	this->forward = this->view.Normalize();
	this->strafeRight = this->up.CrossProduct(this->view).Normalize();

	view = eye + view;

	viewMatrix = Matrix4::CreateLookAt(this->eye, this->view, this->up);

	/*printf("viewMatrix:\n");
	for(int i=1; i<=16; i++){
		printf("%f\t", viewMatrix((i-1) / 4, (i-1) % 4));
		if(i % 4 == 0)
			printf("\n");
	}
	printf("\n");
	printf("\n");*/
}

