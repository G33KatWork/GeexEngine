#include <Math/Vector4.h>
#include <cmath>

#include <Math/Matrix4.h>

Vector4::Vector4()
{
    x = y = z = w = 0.0f;
}

Vector4::Vector4(const Vector4& v)
{
    x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

// assignment
Vector4& Vector4::operator= (const Vector4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
    return *this;
}

// comparison
bool Vector4::operator== (const Vector4& v) const
{
	//double rounding
	return (
		(((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
		(((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))) &&
		(((v.z - 0.0001f) < z) && (z < (v.z + 0.0001f))) &&
		(((v.w - 0.0001f) < w) && (w < (v.w + 0.0001f)))
	);
}

bool Vector4::operator!= (const Vector4& v) const
{
	return !(*this == v);
}

// arithmetic operations
Vector4 Vector4::operator+ (const Vector4& v) const
{
	Vector4 sum;
	sum.x = x + v.x;
	sum.y = y + v.y;
	sum.z = z + v.z;
	sum.w = w + v.w;
    return sum;
}

Vector4 Vector4::operator- (const Vector4& v) const
{
	Vector4 sum;
	sum.x = x - v.x;
	sum.y = y - v.y;
	sum.z = z - v.z;
	sum.w = w - v.w;
    return sum;
}

Vector4 Vector4::operator* (float f) const
{
	Vector4 scaled;
	scaled.x = x * f;
	scaled.y = y * f;
	scaled.z = z * f;
	scaled.w = w * f;
	return scaled;
}

Vector4 Vector4::operator/ (float f) const
{
	Vector4 scaled;
	scaled.x = x / f;
	scaled.y = y / f;
	scaled.z = z / f;
	scaled.w = w / f;
	return scaled;
}

Vector4 Vector4::operator- () const
{
	Vector4 neg;
	neg.x = -x;
	neg.y = -y;
	neg.z = -z;
	neg.w = -w;
	return neg;
}

// arithmetic updates
void Vector4::operator+= (const Vector4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vector4::operator-= (const Vector4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}

Vector4& Vector4::operator*= (float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	this->w *= f;
	return *this;
}

Vector4& Vector4::operator/= (float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
	this->w /= f;
	return *this;
}

// vector times matrix
Vector4 Vector4::operator* (const Matrix4& m) const
{
	Vector4 transformed = Vector4(
		this->x*m(0,0) + this->y*m(1,0) + this->z*m(1,0) + this->w*m(3,0),
		this->x*m(0,1) + this->y*m(1,1) + this->z*m(2,1) + this->w*m(3,1),
		this->x*m(0,2) + this->y*m(1,2) + this->z*m(2,2) + this->w*m(3,2),
		this->x*m(0,3) + this->y*m(1,3) + this->z*m(2,3) + this->w*m(3,3)
	);
	return transformed;
}

// misc operations
float Vector4::ScalarProduct(const Vector4& other) const
{
	return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}

float Vector4::Magnitude() const
{
	float mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
	return mag;
}

Vector4 Vector4::Normalize() const
{
	Vector4 normalized = *this / this->Magnitude();
	return normalized;
}
