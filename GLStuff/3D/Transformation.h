#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_

#include <Math/Matrix4.h>

class Transformation
{
private:
    Matrix4 matrix;
    Matrix4 rotation;
    Vector3 scaling;

public:
    Transformation(void);
    ~Transformation(void);

    void ApplyRotation(const Matrix4& rotation);
    const Matrix4& GetRotation() const;

    void ApplyMatrix(const Matrix4& matrix);
    const Matrix4& GetMatrix() const;

    void ApplyScaling(const Vector3& scaling);
    const Vector3& GetScaling() const;

    void SetUniformScaling(float scaling);
    float GetUniformScaling() const;

};

#endif
