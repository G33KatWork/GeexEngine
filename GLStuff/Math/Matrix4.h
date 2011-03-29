#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <Math/Vector3.h>

class Matrix4
{
public:
    Matrix4();
    Matrix4(const Matrix4& m);
    Matrix4(float _00, float _01, float _02, float _03,
            float _10, float _11, float _12, float _13,
            float _20, float _21, float _22, float _23,
            float _30, float _31, float _32, float _33);

	static Matrix4 Zero();
    static Matrix4 Identity();
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

    // assignment
    Matrix4& operator= (const Matrix4& m);

    //access
    float operator() (int row, int col) const;
    float* operator[] (int row);

    // comparison
    bool operator== (const Matrix4& m) const;
    bool operator!= (const Matrix4& m) const;
    bool operator<  (const Matrix4& m) const;
    bool operator<= (const Matrix4& m) const;
    bool operator>  (const Matrix4& m) const;
    bool operator>= (const Matrix4& m) const;

    // arithmetic operations
    Matrix4 operator+ (const Matrix4& m) const;
    Matrix4 operator- (const Matrix4& m) const;
    Matrix4 operator* (const Matrix4& m) const;
    Matrix4 operator* (float f) const;
    Matrix4 operator/ (float f) const;
    Matrix4 operator- () const;

    // arithmetic updates
    Matrix4& operator+= (const Matrix4& m);
    Matrix4& operator-= (const Matrix4& m);
    Matrix4& operator*= (float f);
    Matrix4& operator/= (float f);

	// other
	//FIXME: implement
	//Matrix4 Transpose () const;

    // matrix times vector
    //Vector3 operator* (const Vector3& v) const;  // M * v

private:
    float a[16];

    static int I(int row, int col)
    {
        return col + 4*row;
    }
};

#endif
