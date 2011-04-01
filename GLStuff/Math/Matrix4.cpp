#define _USE_MATH_DEFINES
#include <cmath>

#include <Math/Matrix4.h>
#include <string.h>
#include <limits>

Matrix4::Matrix4()
{
    memset(a, 0, sizeof(a));
}

Matrix4::Matrix4(const Matrix4& m)
{
    memcpy(a, m.a, sizeof(a));
}

Matrix4::Matrix4(float _00, float _01, float _02, float _03,
        float _10, float _11, float _12, float _13,
        float _20, float _21, float _22, float _23,
        float _30, float _31, float _32, float _33)
{
    a[0] = _00;
    a[1] = _01;
    a[2] = _02;
    a[3] = _03;
    a[4] = _10;
    a[5] = _11;
    a[6] = _12;
    a[7] = _13;
    a[8] = _20;
    a[9] = _21;
    a[10] = _22;
    a[11] = _23;
    a[12] = _30;
    a[13] = _31;
    a[14] = _32;
    a[15] = _33;
}

Matrix4 Matrix4::Zero()
{
    return Matrix4();
}

Matrix4 Matrix4::Identity()
{
    return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::Translate(float dx, float dy, float dz)
{
    Matrix4 translation = Identity();
    translation[3][0] = dx;
    translation[3][1] = dy;
    translation[3][2] = dz;
    return translation;
}

Matrix4 Matrix4::Translate(Vector3& v)
{
    Matrix4 translation = Identity();
    translation[3][0] = v.GetX();
    translation[3][1] = v.GetY();
    translation[3][2] = v.GetZ();
    return translation;
}

Matrix4 Matrix4::Rotate(float angle, float x, float y, float z)
{
    return Matrix4::Rotate(angle, Vector3(x,y,z));
}

Matrix4 Matrix4::Rotate(float angle, Vector3& factors)
{
    Matrix4 rotation;

    Vector3 f = factors.Normalize();
    float x = f.GetX();
    float y = f.GetY();
    float z = f.GetZ();
    float s = sin(angle);
    float c = cos(angle);

    rotation[0][0] = x*x * (1-c) + c;
    rotation[0][1] = x*y * (1-c) + z*s;
    rotation[0][2] = x*z * (1-c) - y*s;
    rotation[0][3] = 0.0f;

    rotation[1][0] = y*x * (1-c) - z*s;
    rotation[1][1] = y*y * (1-c) + c;
    rotation[1][2] = y*z * (1-c) + x*s;
    rotation[1][3] = 0.0f;

    rotation[2][0] = x*z * (1-c) + y*s;
    rotation[2][1] = y*z * (1-c) - x*s;
    rotation[2][2] = z*z * (1-c) + c;
    rotation[2][3] = 0.0f;

    rotation[3][0] = 0.0f;
    rotation[3][1] = 0.0f;
    rotation[3][2] = 0.0f;
    rotation[3][3] = 1.0f;

    return rotation;
}

Matrix4 Matrix4::Scale(float x, float y, float z)
{
    return Matrix4::Scale(Vector3(x,y,z));
}

Matrix4 Matrix4::Scale(Vector3& factors)
{
    Matrix4 scaled = Matrix4::Identity();

    scaled[0][0] = factors.GetX();
    scaled[1][1] = factors.GetY();
    scaled[2][2] = factors.GetZ();

    return scaled;
}

//Create a right-handed perspective projection-matrix with given field-of-view and aspect-ratio
Matrix4 Matrix4::CreatePerspectiveRightHanded(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    Matrix4 perspective = Matrix4::Identity();

    perspective[0][0] = 1.0f / (aspectRatio * tan(fieldOfView/2.0f));
    perspective[1][1] = 1.0f / tan(fieldOfView/2.0f);
    perspective[2][2] = farPlane / (nearPlane - farPlane);
    perspective[2][3] = -1.0f;
    perspective[3][2] = (farPlane * nearPlane) / (nearPlane - farPlane);
    perspective[3][3] = 0.0f;

    return perspective;
}

Matrix4 Matrix4::CreatePerspectiveLeftHanded(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    Matrix4 perspective = Matrix4::Identity();

    perspective[0][0] = 1.0f / (aspectRatio * tan(fieldOfView/2.0f));
    perspective[1][1] = 1.0f / tan(fieldOfView/2.0f);
    perspective[2][2] = farPlane / (farPlane - nearPlane);
    perspective[2][3] = 1.0f;
    perspective[3][2] = (farPlane * nearPlane) / (nearPlane - farPlane);
    perspective[3][3] = 0.0f;

    return perspective;
}

//Create an orthographic projection-matrix with the given planes as borders
Matrix4 Matrix4::CreateOrthographicRightHanded(float left, float right, float top, float bottom, float nearPlane, float farPlane)
{
    Matrix4 orthographic = Matrix4::Identity();

    orthographic[0][0] = 2.0f / (right - left);
    orthographic[1][1] = 2.0f / (top - bottom);
    orthographic[2][2] = 1.0f / (nearPlane - farPlane);
    orthographic[3][0] = -1.0f -2.0f * left / (right - left);
    orthographic[3][1] = 1.0f + 2.0f * top / (bottom - top);
    orthographic[3][2] = nearPlane / (nearPlane - farPlane);

    return orthographic;
}

Matrix4 Matrix4::CreateOrthographicRightHandedCenter(float width, float height, float nearPlane, float farPlane)
{
    Matrix4 orthographic = Matrix4::Identity();

    orthographic[0][0] = 2.0f / width;
    orthographic[1][1] = 2.0f / height;
    orthographic[2][2] = 1.0f / (nearPlane - farPlane);
    orthographic[3][2] = nearPlane / (nearPlane - farPlane);

    return orthographic;
}

Matrix4 Matrix4::CreateLookAtRightHanded(Vector3& position, Vector3& lookAt, Vector3& upVector)
{
    Matrix4 perspective = Matrix4::Zero();

    Vector3 forward = (lookAt - position).Normalize();
    Vector3 right = upVector.CrossProduct(forward).Normalize();
    Vector3 up = forward.CrossProduct(right).Normalize();

    perspective[0][0] = -right.GetX();
    perspective[1][0] = -right.GetY();
    perspective[2][0] = -right.GetZ();
    perspective[3][0] = right.ScalarProduct(position);
    perspective[0][1] = up.GetX();
    perspective[1][1] = up.GetY();
    perspective[2][1] = up.GetZ();
    perspective[3][1] = -up.ScalarProduct(position);
    perspective[0][2] = -forward.GetX();
    perspective[1][2] = -forward.GetY();
    perspective[2][2] = -forward.GetZ();
    perspective[3][2] = forward.ScalarProduct(position);
    perspective[0][3] = 0.0f;
    perspective[1][3] = 0.0f;
    perspective[2][3] = 0.0f;
    perspective[3][3] = 1.0f;

    return perspective;
}

// assignment
Matrix4& Matrix4::operator= (const Matrix4& m)
{
    memcpy(a, m.a, sizeof(a));
    return *this;
}

//access
float Matrix4::operator() (int row, int col) const
{
    return a[I(row, col)];
}

float* Matrix4::operator[] (int row)
{
    return &a[row*4];
}

// comparison
bool Matrix4::operator== (const Matrix4& m) const
{
    return memcmp(a, m.a, sizeof(a)) == 0;
}

bool Matrix4::operator!= (const Matrix4& m) const
{
    return memcmp(a, m.a, sizeof(a)) != 0;
}

bool Matrix4::operator<  (const Matrix4& m) const
{
    return memcmp(a, m.a, sizeof(a)) < 0;
}

bool Matrix4::operator<= (const Matrix4& m) const
{
    return memcmp(a, m.a, sizeof(a)) <= 0;
}

bool Matrix4::operator>  (const Matrix4& m) const
{
    return memcmp(a, m.a, sizeof(a)) > 0;
}

bool Matrix4::operator>= (const Matrix4& m) const
{
    return memcmp(a, m.a, sizeof(a)) >= 0;
}

// arithmetic operations
Matrix4 Matrix4::operator+ (const Matrix4& m) const
{
    Matrix4 sum;
    for(int i = 0; i < 16; i++)
        sum.a[i] = a[i] + m.a[i];

    return sum;
}

Matrix4 Matrix4::operator- (const Matrix4& m) const
{
    Matrix4 dif;
    for(int i = 0; i < 16; i++)
        dif.a[i] = a[i] - m.a[i];

    return dif;
}

Matrix4 Matrix4::operator* (const Matrix4& other) const
{
    Matrix4 prod;

    Matrix4 me = *this;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            prod[i][j] = me[i][0] * other(0,j) + me[i][1] * other(1,j) + me[i][2] * other(2,j) + me[i][3] * other(3,j);

    return prod;
}

Matrix4 Matrix4::operator* (float f) const
{
    Matrix4 scaled;
    for(int i = 0; i < 16; i++)
        scaled.a[i] = a[i] * f;
    return scaled;
}

Matrix4 Matrix4::operator/ (float f) const
{
    Matrix4 scaled;

    if(f != 0.0f)
    {
        float inv = 1/f;
        for(int i = 0; i < 16; i++)
            scaled.a[i] = inv * a[i];
    }
    else
    {
        for(int i = 0; i < 16; i++)
            scaled.a[i] = std::numeric_limits<float>::max();
    }

    return scaled;
}

Matrix4 Matrix4::operator- () const
{
    Matrix4 neg;
    for(int i = 0; i < 16; i++)
        neg.a[i] = -a[i];
    return neg;
}

// arithmetic updates
Matrix4& Matrix4::operator+= (const Matrix4& m)
{
    for(int i = 0; i < 16; i++)
        a[i] = a[i] + m.a[i];

    return *this;
}

Matrix4& Matrix4::operator-= (const Matrix4& m)
{
    for(int i = 0; i < 16; i++)
        a[i] = a[i] - m.a[i];

    return *this;
}

Matrix4& Matrix4::operator*= (float f)
{
    for(int i = 0; i < 16; i++)
        a[i] = a[i] * f;

    return *this;
}

Matrix4& Matrix4::operator/= (float f)
{
    if(f != 0.0f)
    {
        float inv = 1/f;
        for(int i = 0; i < 16; i++)
            a[i] = inv * a[i];
    }
    else
    {
        for(int i = 0; i < 16; i++)
            a[i] = std::numeric_limits<float>::max();
    }

    return *this;
}

// matrix times vector
/*Vector3 Matrix4::operator* (const Vector3& v) const
{
    Vector3 result = Vector3(
        this->a[0]*v.GetX() + this->a[1]*v.GetY() + this->a[2]*v.GetY() + this->a[3]*1,
        this->a[4]*v.GetX() + this->a[5]*v.GetY() + this->a[6]*v.GetY() + this->a[7]*1,
        this->a[8]*v.GetX() + this->a[9]*v.GetY() + this->a[10]*v.GetY() + this->a[11]*1
    );
    return result;
}*/
