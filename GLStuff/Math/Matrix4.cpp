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
	translation[0][3] = dx;
	translation[1][3] = dy;
	translation[2][3] = dz;
	return translation;
}

Matrix4 Matrix4::Translate(Vector3& v)
{
	Matrix4 translation = Identity();
	translation[0][3] = v.GetX();
	translation[1][3] = v.GetY();
	translation[2][3] = v.GetZ();
	return translation;
}

Matrix4 Matrix4::Rotate(float angle, float x, float y, float z)
{
	return Matrix4::Rotate(angle, Vector3(x,y,z));
}

Matrix4 Matrix4::Rotate(float angle, Vector3& factors)
{
	//see http://wiki.delphigl.com/index.php/glRotate

	Matrix4 rotation;

	Vector3 f = factors.Normalize();
	float x = f.GetX();
	float y = f.GetY();
	float z = f.GetZ();
	float s = sin(angle);
	float c = cos(angle);

	rotation[0][0] = x*x * (1-c) + c;
	rotation[0][1] = x*y * (1-c) - z*s;
	rotation[0][2] = y*z * (1-c) + y*s;
	rotation[0][3] = 0.0f;

	rotation[1][0] = y*x * (1-c) + z*s;
	rotation[1][1] = y*y * (1-c) + c;
	rotation[1][2] = y*z * (1-c) - x*s;
	rotation[1][3] = 0.0f;

	rotation[2][0] = x*z * (1-c) - y*s;
	rotation[2][1] = y*z * (1-c) + x*s;
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
Matrix4 Matrix4::CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	Matrix4 perspective = Matrix4::Zero();

	//cot(x) = tan(PI/2 - x)
	float f = (float)tan(M_PI_2 - ((fieldOfView*(float)M_PI/180.0f)/2.0f));
	
	perspective[0][0] = f/aspectRatio;
	perspective[1][1] = f;
	perspective[2][2] = (farPlane+nearPlane) / (nearPlane-farPlane);
	perspective[2][3] = (2*farPlane*nearPlane) / (nearPlane-farPlane);
	perspective[3][2] = -1.0f;	//right-handed, left-handed would be 1.0f

	return perspective;
}

//Create an orthographic projection-matrix with the given planes as borders
Matrix4 Matrix4::CreateOrthographic(float left, float right, float top, float bottom, float nearPlane, float farPlane)
{
	//see http://www.codeguru.com/cpp/misc/misc/math/article.php/c10123
	Matrix4 orthographic = Matrix4::Zero();

	orthographic[0][0] = 2 / (right-left);
	orthographic[0][1] = 0.0f;
	orthographic[0][2] = 0.0f;
	orthographic[0][3] = 0.0f;

	orthographic[1][0] = 0.0f;
	orthographic[1][1] = 2 / (top-bottom);
	orthographic[1][2] = 0.0f;
	orthographic[1][3] = 0.0f;

	orthographic[2][0] = 0.0f;
	orthographic[2][1] = 0.0f;
	orthographic[2][2] = 1.0f / (nearPlane-farPlane);		//right-handed, left-handed would be 1.0f / (farPlane-nearPlane)
	orthographic[2][3] = 0.0f;

	orthographic[3][0] = (left+right) / (left-right);
	orthographic[3][1] = (top+bottom) / (bottom-top);
	orthographic[3][2] = nearPlane / (nearPlane-farPlane);
	orthographic[3][3] = 1.0f;

	return orthographic;
}

Matrix4 Matrix4::CreateOrthographicCenter(float width, float height, float nearPlane, float farPlane)
{
	//see http://www.codeguru.com/cpp/misc/misc/math/article.php/c10123
	Matrix4 orthographic = Matrix4::Zero();

	orthographic[0][0] = 2 / width;
	orthographic[0][1] = 0.0f;
	orthographic[0][2] = 0.0f;
	orthographic[0][3] = 0.0f;

	orthographic[1][0] = 0.0f;
	orthographic[1][1] = 2 / height;
	orthographic[1][2] = 0.0f;
	orthographic[1][3] = 0.0f;

	orthographic[2][0] = 0.0f;
	orthographic[2][1] = 0.0f;
	orthographic[2][2] = 1.0f / (nearPlane-farPlane);			//right-handed, left-handed would be 1 / (farPlane - nearPlane)
	orthographic[2][3] = 0.0f;

	orthographic[3][0] = 0.0f;
	orthographic[3][1] = 0.0f;
	orthographic[3][2] = nearPlane / (nearPlane-farPlane);		//right-handed, left-handed would be -nearPlane / (farPlane-nearPlane)
	orthographic[3][3] = 1.0f;

	return orthographic;
}

Matrix4 Matrix4::CreateLookAt(Vector3& position, Vector3& lookAt, Vector3& upVector)
{
	//see http://wiki.delphigl.com/index.php/gluLookAt
	//or http://www.opengl.org/wiki/GluLookAt_code

	Matrix4 perspective = Matrix4::Zero();

	Vector3 forward = (position - lookAt).Normalize();
	Vector3 side = forward.CrossProduct(upVector).Normalize();
	Vector3 up = side.CrossProduct(forward);

	perspective[0][0] = side.GetX();
	perspective[0][1] = side.GetY();
	perspective[0][2] = side.GetZ();
	perspective[0][3] = 0.0f;

	perspective[1][0] = up.GetX();
	perspective[1][1] = up.GetY();
	perspective[1][2] = up.GetZ();
	perspective[1][3] = 0.0f;

	perspective[2][0] = -(forward.GetX());
	perspective[2][1] = -(forward.GetY());
	perspective[2][2] = -(forward.GetZ());
	perspective[2][3] = 0.0f;

	perspective[3][0] = 0.0f;
	perspective[3][1] = 0.0f;
	perspective[3][2] = 0.0f;
	perspective[3][3] = 1.0f;

	perspective = perspective * Matrix4::Translate(-position);

	//Code from DirectX Documentation
	/*Matrix4 perspective = Matrix4::Zero();

	Vector3 forward = (position - lookAt).Normalize();		//right-handed, left-handed would be lookAt-position
	Vector3 side = upVector.CrossProduct(forward).Normalize();
	Vector3 up = forward.CrossProduct(side);

	perspective[0][0] = side.GetX();
	perspective[0][1] = up.GetX();
	perspective[0][2] = forward.GetX();
	perspective[0][3] = 0.0f;

	perspective[1][0] = side.GetY();
	perspective[1][1] = up.GetY();
	perspective[1][2] = forward.GetY();
	perspective[1][3] = 0.0f;

	perspective[2][0] = side.GetZ();
	perspective[2][1] = up.GetZ();
	perspective[2][2] = forward.GetZ();
	perspective[2][3] = 0.0f;

	perspective[3][0] = -side.ScalarProduct(position);
	perspective[3][1] = -up.ScalarProduct(position);
	perspective[3][2] = -forward.ScalarProduct(position);
	perspective[3][3] = 1.0f;*/

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

Matrix4 Matrix4::operator* (const Matrix4& m) const
{
	Matrix4 prod;

	prod.a[0] = a[0]*m.a[0] + a[1]*m.a[4] + a[2]*m.a[8] + a[3]*m.a[12];
	prod.a[1] = a[0]*m.a[1] + a[1]*m.a[5] + a[2]*m.a[9] + a[3]*m.a[13];
	prod.a[2] = a[0]*m.a[2] + a[1]*m.a[6] + a[2]*m.a[10] + a[3]*m.a[14];
	prod.a[3] = a[0]*m.a[3] + a[1]*m.a[7] + a[2]*m.a[11] + a[3]*m.a[15];

	prod.a[4] = a[4]*m.a[0] + a[5]*m.a[4] + a[6]*m.a[8] + a[7]*m.a[12];
	prod.a[5] = a[4]*m.a[1] + a[5]*m.a[5] + a[6]*m.a[9] + a[7]*m.a[13];
	prod.a[6] = a[4]*m.a[2] + a[5]*m.a[6] + a[6]*m.a[10] + a[7]*m.a[14];
	prod.a[7] = a[4]*m.a[3] + a[5]*m.a[7] + a[6]*m.a[11] + a[7]*m.a[15];

	prod.a[8] = a[8]*m.a[0] + a[9]*m.a[4] + a[10]*m.a[8] + a[11]*m.a[12];
	prod.a[9] = a[8]*m.a[1] + a[9]*m.a[5] + a[10]*m.a[9] + a[11]*m.a[13];
	prod.a[10] = a[8]*m.a[2] + a[9]*m.a[6] + a[10]*m.a[10] + a[11]*m.a[14];
	prod.a[11] = a[8]*m.a[3] + a[9]*m.a[7] + a[10]*m.a[11] + a[11]*m.a[15];

	prod.a[12] = a[12]*m.a[0] + a[13]*m.a[4] + a[14]*m.a[8] + a[15]*m.a[12];
	prod.a[13] = a[12]*m.a[1] + a[13]*m.a[5] + a[14]*m.a[9] + a[15]*m.a[13];
	prod.a[14] = a[12]*m.a[2] + a[13]*m.a[6] + a[14]*m.a[10] + a[15]*m.a[14];
	prod.a[15] = a[12]*m.a[3] + a[13]*m.a[7] + a[14]*m.a[11] + a[15]*m.a[15];

    /*for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            int i = I(row, col);
            prod.a[i] = 0.0f;

            for(int mid = 0; mid < 4; mid++)
                prod.a[I(row, mid)] += a[I(row, mid)] * m.a[I(mid, col)];
        }
    }*/

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
