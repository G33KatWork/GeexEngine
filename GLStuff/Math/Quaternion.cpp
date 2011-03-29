#include <Math/Quaternion.h>
#include <cmath>

Quaternion::Quaternion()
{
	x = y = z = w = 0.0f;
}

Quaternion::Quaternion(const Quaternion& m)
{
	this->x = m.x;
	this->y = m.y;
	this->z = m.z;
	this->w = m.w;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion Quaternion::Zero()
{
	return Quaternion();
}

Quaternion Quaternion::Identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::CreateFromAxisAngle(float x, float y, float z, float angle)
{
	float r = sin(angle / 2.0f);

	Quaternion q = Quaternion(
		x * r,
		y * r,
		z * r,
		cos(angle / 2.0f)
	);
	return q;
}

// assignment
Quaternion& Quaternion::operator= (const Quaternion& q)
{
    this->x = q.x;
	this->y = q.y;
	this->z = q.z;
	this->w = q.w;
    return *this;
}

// arithmetic operations
Quaternion Quaternion::operator+ (const Quaternion& q) const
{
	Quaternion sum = Quaternion(
		this->x + q.x,
		this->y + q.y,
		this->z + q.z,
		this->w + q.w
	);
	return sum;
}

Quaternion Quaternion::operator- (const Quaternion& q) const
{
	Quaternion dif = Quaternion(
		this->x - q.x,
		this->y - q.y,
		this->z - q.z,
		this->w - q.w
	);
	return dif;
}

Quaternion Quaternion::operator* (const Quaternion& q) const
{
	Quaternion product(
		this->w*q.x + this->x*q.w + this->y*q.z - this->z*q.y,
		this->w*q.y + this->y*q.w + this->z*q.x - this->x*q.z,
		this->w*q.z + this->z*q.w + this->x*q.y - this->y*q.x,
		this->w*q.w - this->x*q.x - this->y*q.y - this->z*q.z
	);
	return product;
}

/*Quaternion Quaternion::operator/ (const Quaternion& m) const
{
	
}*/

//misc
Matrix4 Quaternion::CreateMatrix() const
{
	Matrix4 m = Matrix4(
		1.0f - 2.0f * (this->y * this->y + this->z * this->z),
		2.0f * (this->x * this->y + this->z * this->w),
		2.0f * (this->x * this->z - this->y * this->w),
		0.0f,

		2.0f * (this->x * this->y - this->z * this->w),
		2.0f - 2.0f * (this->x * this->x + this->z * this->z),
		2.0f * (this->z * this->y + this->x * this->w),
		0.0f,

		2.0f * (this->x * this->z + this->y * this->w),
		2.0f * (this->y * this->z - this->x * this->w),
		1.0f - 2.0f * (this->x * this->x + this->y * this->y),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
	return m;
}