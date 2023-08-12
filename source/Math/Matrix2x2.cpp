#include "Matrix2x2.h"


float Matrix2x2::Determinant() const
{
    return (Column[0].X * Column[1].Y) - (Column[0].Y * Column[1].X);
}

Matrix2x2 Matrix2x2::Tansponed() const
{
    return {{ Column[0].X, Column[1].X },
            { Column[0].Y, Column[1].Y }};
}

Matrix2x2 Matrix2x2::Inverted() const
{
    float det = 1.0f / Determinant();
    return {{ det* Column[1].Y, det* (-Column[0].Y)},
            {det* (-Column[1].X), det* Column[0].X} };
}

Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& Other)
{
    Column[0] += Other.Column[0];
    Column[1] += Other.Column[1];
    return *this;
}

Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& Other)
{
    Column[0] -= Other.Column[0];
    Column[1] -= Other.Column[1];
    return *this;
}

Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& Other)
{
    Matrix2x2 result = *this * Other;
    *this = result;
    return *this;
}

Matrix2x2& Matrix2x2::operator*=(float Scalar)
{
    Column[0] *= Scalar;
    Column[1] *= Scalar;
    return *this;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2& Other) const
{
    Matrix2x2 result;
    result.Column[0] = Column[0] + Other.Column[0];
    result.Column[1] = Column[1] + Other.Column[1];
    return result;
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& Other) const
{
    Matrix2x2 result;
    result.Column[0] = Column[0] - Other.Column[0];
    result.Column[1] = Column[1] - Other.Column[1];
    return result;
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2& Other) const
{
    Matrix2x2 result;
    result.Column[0].X = Column[0].X * Other.Column[0].X + Column[1].X * Other.Column[0].Y;
    result.Column[0].Y = Column[0].Y * Other.Column[0].X + Column[1].Y * Other.Column[0].Y;
    result.Column[1].X = Column[0].X * Other.Column[1].X + Column[1].X * Other.Column[1].Y;
    result.Column[1].Y = Column[0].Y * Other.Column[1].X + Column[1].Y * Other.Column[1].Y;
    return result;
}

Float2 Matrix2x2::operator*(const Float2& Other) const
{
    Float2 result;
    result.X = Column[0].X * Other.X + Column[1].X * Other.Y;
    result.Y = Column[0].Y * Other.X + Column[1].Y * Other.Y;
    return result;
}

Matrix2x2 Matrix2x2::operator*(float Scalar) const
{
    return *this * Scalar;
}
