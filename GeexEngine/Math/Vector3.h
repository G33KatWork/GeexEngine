#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <Common/GeexEngineExports.h>

class Matrix4;

class GEEXENGINE_API Vector3
{
private:
    float x, y, z;

public:
    Vector3();
    Vector3(const Vector3& v);
    Vector3(float x, float y, float z);

    // assignment
    Vector3& operator= (const Vector3& v);

    // access
    float GetX() const { return this->x; }
    float GetY() const { return this->y; }
    float GetZ() const { return this->z; }
    void SetX(float x) { this->x = x; }
    void SetY(float y) { this->y = y; }
    void SetZ(float z) { this->z = z; }
    
    // comparison
    bool operator== (const Vector3& v) const;
    bool operator!= (const Vector3& v) const;

    // arithmetic operations
    Vector3 operator+ (const Vector3& v) const;
    Vector3 operator- (const Vector3& v) const;
    Vector3 operator* (float f) const;
    Vector3 operator/ (float f) const;
    Vector3 operator- () const;

    // arithmetic updates
    void operator+= (const Vector3& v);
    void operator-= (const Vector3& v);
    Vector3& operator*= (float f);
    Vector3& operator/= (float f);

    // vector times matrix
    Vector3 operator* (const Matrix4& m) const;

    // misc operations
    float ScalarProduct(const Vector3& other) const;
    Vector3 CrossProduct(const Vector3& other) const;
    float Magnitude() const;
    Vector3 Normalize() const;
};

#endif
