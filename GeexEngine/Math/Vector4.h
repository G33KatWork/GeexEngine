#ifndef _VECTOR4_H_
#define _VECTOR4_H_

class Matrix4;

class Vector4
{
private:
    float x, y, z, w;

public:
    Vector4();
    Vector4(const Vector4& v);
    Vector4(float x, float y, float z, float w);

    // assignment
    Vector4& operator= (const Vector4& v);

    // access
    float GetX() const { return this->x; }
    float GetY() const { return this->y; }
    float GetZ() const { return this->z; }
    float GetW() const { return this->w; }
    void SetX(float x) { this->x = x; }
    void SetY(float y) { this->y = y; }
    void SetZ(float z) { this->z = z; }
    void SetW(float w) { this->w = w; }
    
    // comparison
    bool operator== (const Vector4& v) const;
    bool operator!= (const Vector4& v) const;

    // arithmetic operations
    Vector4 operator+ (const Vector4& v) const;
    Vector4 operator- (const Vector4& v) const;
    Vector4 operator* (float f) const;
    Vector4 operator/ (float f) const;
    Vector4 operator- () const;

    // arithmetic updates
    void operator+= (const Vector4& v);
    void operator-= (const Vector4& v);
    Vector4& operator*= (float f);
    Vector4& operator/= (float f);

    // vector times matrix
    Vector4 operator* (const Matrix4& m) const;

    // misc operations
    float ScalarProduct(const Vector4& other) const;
    float Magnitude() const;
    Vector4 Normalize() const;
};

#endif
