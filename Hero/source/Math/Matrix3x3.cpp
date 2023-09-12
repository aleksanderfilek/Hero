#include "Matrix3x3.h"

// Matrix3x3::Matrix3x3(const Matrix4x4& matrix)
// {
//     Column[0] = Float3(matrix.Column[0]);
//     Column[1] = Float3(matrix.Column[1]);
//     Column[2] = Float3(matrix.Column[2]);
// }

float Matrix3x3::Determinant() const
{
    return Column[0].X * Column[1].Y * Column[2].Z +
        Column[1].X * Column[2].Y * Column[0].Z +
        Column[2].X * Column[0].Y * Column[1].Z -
        Column[2].X * Column[1].Y * Column[0].Z -
        Column[1].X * Column[0].Y * Column[2].Z -
        Column[0].X * Column[2].Y * Column[1].Z;
}

Matrix3x3 Matrix3x3::Tansponed() const
{
    Matrix3x3 matrix;

    matrix.Column[0].X = Column[0].X;
    matrix.Column[1].X = Column[0].Y;
    matrix.Column[2].X = Column[0].Z;
    matrix.Column[0].Y = Column[1].X;
    matrix.Column[1].Y = Column[1].Y;
    matrix.Column[2].Y = Column[1].Z;
    matrix.Column[0].Z = Column[2].X;
    matrix.Column[1].Z = Column[2].Y;
    matrix.Column[2].Z = Column[2].Z;

    return matrix;
}

Matrix3x3 Matrix3x3::Inverted() const
{
    float det = 1.0f / Determinant();

    Matrix3x3 matrix;

    matrix.Column[0].X = (Column[1].Y * Column[2].Z) - (Column[2].Y * Column[1].Z);
    matrix.Column[0].X *= det;
    matrix.Column[0].Y = (Column[0].Y * Column[2].Z) - (Column[2].Y * Column[0].Z);
    matrix.Column[0].Y *= -det;
    matrix.Column[0].Z = (Column[0].Y * Column[1].Z) - (Column[1].Y * Column[0].Z);
    matrix.Column[0].Z *= det;

    matrix.Column[1].X = (Column[1].X * Column[2].Z) - (Column[2].X * Column[1].Z);
    matrix.Column[1].X *= -det;
    matrix.Column[1].Y = (Column[0].X * Column[2].Z) - (Column[2].X * Column[0].Z);
    matrix.Column[1].Y *= det;
    matrix.Column[1].Z = (Column[0].X * Column[1].Z) - (Column[1].X * Column[0].Z);
    matrix.Column[1].Z *= -det;

    matrix.Column[2].X = (Column[1].X * Column[2].Y) - (Column[2].X * Column[1].Y);
    matrix.Column[2].X *= det;
    matrix.Column[2].Y = (Column[0].X * Column[2].Y) - (Column[2].X * Column[0].Y);
    matrix.Column[2].Y *= -det;
    matrix.Column[2].Z = (Column[0].X * Column[1].Y) - (Column[1].X * Column[0].Y);
    matrix.Column[2].Z *= det;

    return matrix;
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& Other)
{
    Column[0] += Other.Column[0];
    Column[1] += Other.Column[1];
    Column[2] += Other.Column[2];
    return *this;
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& Other)
{
    Column[0] -= Other.Column[0];
    Column[1] -= Other.Column[1];
    Column[2] -= Other.Column[2];
    return *this;
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& Other)
{
    Matrix3x3 result = *this * Other;
    *this = result;
    return *this;
}

Matrix3x3& Matrix3x3::operator*=(float Scalar)
{
    Column[0] *= Scalar;
    Column[1] *= Scalar;
    Column[2] *= Scalar;
    return *this;
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& Other) const
{
    Matrix3x3 result;
    result.Column[0] = Column[0] + Other.Column[0];
    result.Column[1] = Column[1] + Other.Column[1];
    result.Column[2] = Column[2] + Other.Column[2];
    return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& Other) const
{
    Matrix3x3 result;
    result.Column[0] = Column[0] - Other.Column[0];
    result.Column[1] = Column[1] - Other.Column[1];
    result.Column[2] = Column[2] - Other.Column[2];
    return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& Other) const
{
    Matrix3x3 matrix;

    matrix.Column[0].X = Column[0].X * Other.Column[0].X + Column[1].X * Other.Column[0].Y + Column[2].X * Other.Column[0].Z;
    matrix.Column[0].Y = Column[0].Y * Other.Column[0].X + Column[1].Y * Other.Column[0].Y + Column[2].Y * Other.Column[0].Z;
    matrix.Column[0].Z = Column[0].Z * Other.Column[0].X + Column[1].Z * Other.Column[0].Y + Column[2].Z * Other.Column[0].Z;

    matrix.Column[1].X = Column[0].X * Other.Column[1].X + Column[1].X * Other.Column[1].Y + Column[2].X * Other.Column[1].Z;
    matrix.Column[1].Y = Column[0].Y * Other.Column[1].X + Column[1].Y * Other.Column[1].Y + Column[2].Y * Other.Column[1].Z;
    matrix.Column[1].Z = Column[0].Z * Other.Column[1].X + Column[1].Z * Other.Column[1].Y + Column[2].Z * Other.Column[1].Z;

    matrix.Column[2].X = Column[0].X * Other.Column[2].X + Column[1].X * Other.Column[2].Y + Column[2].X * Other.Column[2].Z;
    matrix.Column[2].Y = Column[0].Y * Other.Column[2].X + Column[1].Y * Other.Column[2].Y + Column[2].Y * Other.Column[2].Z;
    matrix.Column[2].Z = Column[0].Z * Other.Column[2].X + Column[1].Z * Other.Column[2].Y + Column[2].Z * Other.Column[2].Z;

    return matrix;
}

Float3 Matrix3x3::operator*(const Float3& Other) const
{
    Float3 vec;
    vec.X = Column[0].X * Other.X + Column[1].X * Other.Y + Column[2].X * Other.Z;
    vec.Y = Column[0].Y * Other.X + Column[1].Y * Other.Y + Column[2].Y * Other.Z;
    vec.Z = Column[0].Z * Other.X + Column[2].Z * Other.Y + Column[2].Z * Other.Z;
    return vec;
}

Matrix3x3 Matrix3x3::operator*(float Scalar) const
{
    Matrix3x3 result;
    result.Column[0] *= Scalar;
    result.Column[1] *= Scalar;
    result.Column[2] *= Scalar;
    return result;
}