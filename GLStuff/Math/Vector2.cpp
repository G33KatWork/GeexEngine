#include <Math/Vector2.h>
#include <cmath>

#include <Math/Matrix4.h>

Vector2::Vector2()
{
    x = y = 0.0f;
}

Vector2::Vector2(const Vector2& v)
{
    x = v.x;
    y = v.y;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

// assignment
Vector2& Vector2::operator= (const Vector2& v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}

// comparison
bool Vector2::operator== (const Vector2& v) const
{
    //double rounding
    return (
        (((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
        (((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f)))
    );
}

bool Vector2::operator!= (const Vector2& v) const
{
    return !(*this == v);
}

// arithmetic operations
Vector2 Vector2::operator+ (const Vector2& v) const
{
    Vector2 sum;
    sum.x = x + v.x;
    sum.y = y + v.y;
    return sum;
}

Vector2 Vector2::operator- (const Vector2& v) const
{
    Vector2 sum;
    sum.x = x - v.x;
    sum.y = y - v.y;
    return sum;
}

Vector2 Vector2::operator* (float f) const
{
    Vector2 scaled;
    scaled.x = x * f;
    scaled.y = y * f;
    return scaled;
}

Vector2 Vector2::operator/ (float f) const
{
    Vector2 scaled;
    scaled.x = x / f;
    scaled.y = y / f;
    return scaled;
}

Vector2 Vector2::operator- () const
{
    Vector2 neg;
    neg.x = -x;
    neg.y = -y;
    return neg;
}

// arithmetic updates
void Vector2::operator+= (const Vector2& v)
{
    this->x += v.x;
    this->y += v.y;
}

void Vector2::operator-= (const Vector2& v)
{
    this->x -= v.x;
    this->y -= v.y;
}

Vector2& Vector2::operator*= (float f)
{
    this->x *= f;
    this->y *= f;
    return *this;
}

Vector2& Vector2::operator/= (float f)
{
    this->x /= f;
    this->y /= f;
    return *this;
}

// vector times matrix
Vector2 Vector2::operator* (const Matrix4& m) const
{
    Vector2 transformed = Vector2(
        this->x*m(0,0) + this->y*m(1,0) + 0*m(1,0) + 1*m(3,0),
        this->x*m(0,1) + this->y*m(1,1) + 0*m(2,1) + 1*m(3,1)	
    );
    return transformed;
}

// misc operations
float Vector2::ScalarProduct(const Vector2& other) const
{
    return this->x * other.x + this->y * other.y;
}

float Vector2::Magnitude() const
{
    return sqrt(this->x * this->x + this->y * this->y);
}

Vector2 Vector2::Normalize() const
{
    return *this / this->Magnitude();
}
