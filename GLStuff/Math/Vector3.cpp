#include <Math/Vector3.h>
#include <cmath>

#include <Math/Matrix4.h>

Vector3::Vector3()
{
    x = y = z = 0.0f;
}

Vector3::Vector3(const Vector3& v)
{
    x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
	this->y = y;
	this->z = z;
}

// assignment
Vector3& Vector3::operator= (const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
    return *this;
}

// comparison
bool Vector3::operator== (const Vector3& v) const
{
	//double rounding
	return (
		(((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
		(((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))) &&
		(((v.z - 0.0001f) < z) && (z < (v.z + 0.0001f)))
	);
}

bool Vector3::operator!= (const Vector3& v) const
{
	return !(*this == v);
}

// arithmetic operations
Vector3 Vector3::operator+ (const Vector3& v) const
{
	Vector3 sum;
	sum.x = x + v.x;
	sum.y = y + v.y;
	sum.z = z + v.z;
    return sum;
}

Vector3 Vector3::operator- (const Vector3& v) const
{
	Vector3 sum;
	sum.x = x - v.x;
	sum.y = y - v.y;
	sum.z = z - v.z;
    return sum;
}

Vector3 Vector3::operator* (float f) const
{
	Vector3 scaled;
	scaled.x = x * f;
	scaled.y = y * f;
	scaled.z = z * f;
	return scaled;
}

Vector3 Vector3::operator/ (float f) const
{
	Vector3 scaled;
	scaled.x = x / f;
	scaled.y = y / f;
	scaled.z = z / f;
	return scaled;
}

Vector3 Vector3::operator- () const
{
	Vector3 neg;
	neg.x = -x;
	neg.y = -y;
	neg.z = -z;
	return neg;
}

// arithmetic updates
void Vector3::operator+= (const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vector3::operator-= (const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

Vector3& Vector3::operator*= (float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}

Vector3& Vector3::operator/= (float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}

// vector times matrix
Vector3 Vector3::operator* (const Matrix4& m) const
{
	Vector3 transformed = Vector3(
		this->x*m(0,0) + this->y*m(1,0) + this->z*m(1,0) + 1*m(3,0),
		this->x*m(0,1) + this->y*m(1,1) + this->z*m(2,1) + 1*m(3,1),
		this->x*m(0,2) + this->y*m(1,2) + this->z*m(2,2) + 1*m(3,2)
	);
	return transformed;
}

// misc operations
float Vector3::ScalarProduct(const Vector3& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::CrossProduct(const Vector3& other) const
{
	Vector3 result;
	result.x = this->y * other.z - this->z * other.y;
	result.y = this->z * other.x - this->x * other.z;
	result.z = this->x * other.y - this->y * other.x;
	return result;
}

float Vector3::Magnitude() const
{
	float mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	return mag;
}

Vector3 Vector3::Normalize() const
{
	Vector3 normalized = *this / this->Magnitude();
	return normalized;
}
