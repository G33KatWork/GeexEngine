#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Matrix4;

class Vector2
{
private:
    float x, y;

public:
    Vector2();
    Vector2(const Vector2& v);
    Vector2(float x, float y);

    // assignment
    Vector2& operator= (const Vector2& v);

    // access
    float GetX() const { return this->x; }
    float GetY() const { return this->y; }
    void SetX(float x) { this->x = x; }
    void SetY(float y) { this->y = y; }
    
    // comparison
    bool operator== (const Vector2& v) const;
    bool operator!= (const Vector2& v) const;

    // arithmetic operations
    Vector2 operator+ (const Vector2& v) const;
    Vector2 operator- (const Vector2& v) const;
    Vector2 operator* (float f) const;
    Vector2 operator/ (float f) const;
    Vector2 operator- () const;

    // arithmetic updates
    void operator+= (const Vector2& v);
    void operator-= (const Vector2& v);
    Vector2& operator*= (float f);
    Vector2& operator/= (float f);

    // vector times matrix
    Vector2 operator* (const Matrix4& m) const;

    // misc operations
    float ScalarProduct(const Vector2& other) const;
    float Magnitude() const;
    Vector2 Normalize() const;
};

typedef Vector2 Point;

#endif
