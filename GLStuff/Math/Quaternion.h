#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <Math/Matrix4.h>

class Quaternion
{
public:
	Quaternion();
    Quaternion(const Quaternion& m);
    Quaternion(float x, float y, float z, float w);

	static Quaternion Zero();
    static Quaternion Identity();
	static Quaternion CreateFromAxisAngle(float x, float y, float z, float angle);

	// assignment
    Quaternion& operator= (const Quaternion& q);

	// access
	float GetX() const { return this->x; }
	float GetY() const { return this->y; }
	float GetZ() const { return this->z; }
	float GetW() const { return this->w; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }
	void SetW(float w) { this->w = w; }

	// arithmetic operations
    Quaternion operator+ (const Quaternion& q) const;
    Quaternion operator- (const Quaternion& m) const;
    Quaternion operator* (const Quaternion& m) const;
    //Quaternion operator/ (const Quaternion& m) const;

	//misc
	Matrix4 CreateMatrix() const;

    /*
	static Matrix4 Translate(float dx, float dy, float dz);
	static Matrix4 Translate(Vector3& v);
	static Matrix4 Rotate(float angle, float x, float y, float z);
	static Matrix4 Rotate(float angle, Vector3& factors);
	static Matrix4 Scale(float x, float y, float z);
	static Matrix4 Scale(Vector3& factors);
	static Matrix4 CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	static Matrix4 CreateOrthographic(float left, float right, float top, float bottom, float nearPlane, float farPlane);
	static Matrix4 CreateOrthographicCenter(float width, float height, float nearPlane, float farPlane);
	static Matrix4 CreateLookAt(Vector3& position, Vector3& lookAt, Vector3& upVector);

    // comparison
    bool operator== (const Matrix4& m) const;
    bool operator!= (const Matrix4& m) const;
    bool operator<  (const Matrix4& m) const;
    bool operator<= (const Matrix4& m) const;
    bool operator>  (const Matrix4& m) const;
    bool operator>= (const Matrix4& m) const;

    // arithmetic operations
    Matrix4 operator* (float f) const;
    Matrix4 operator/ (float f) const;
    Matrix4 operator- () const;

    // arithmetic updates
    Matrix4& operator+= (const Matrix4& m);
    Matrix4& operator-= (const Matrix4& m);
    Matrix4& operator*= (float f);
    Matrix4& operator/= (float f);*/

private:
    float x, y, z, w;
};

#endif
