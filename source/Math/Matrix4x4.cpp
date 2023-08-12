#include "Matrix4x4.h"
#include <cmath>
#include "MathConstants.h"

// Matrix4x4::Matrix4x4(const Matrix3x3& Matrix)
// {
//     Column[0] = Float4(Matrix.Column[0]);
//     Column[1] = Float4(Matrix.Column[1]);
//     Column[2] = Float4(Matrix.Column[2]);
//     Column[3] = Float4(0.0f, 0.0f, 0.0f, 1.0f);
// }

float Matrix4x4::Determinent() const
{
    Matrix4x4 Matrix = Matrix4x4::Identity();

    float mul = Column[0].Y / Column[0].X;
    Matrix.Column[1].Y = Column[1].Y - mul * Column[1].X;
    Matrix.Column[2].Y = Column[2].Y - mul * Column[2].X;
    Matrix.Column[3].Y = Column[3].Y - mul * Column[3].X;

    mul = Column[0].Z / Column[0].Y;
    Matrix.Column[2].Z = Column[2].Z - mul * Column[2].Y;
    Matrix.Column[3].Z = Column[3].Z - mul * Column[3].Y;

    mul = Column[0].W / Column[0].Z;
    Matrix.Column[2].W = Column[2].W - mul * Column[2].Z;

    return Matrix.Column[0].X * Matrix.Column[1].Y * Matrix.Column[2].Z * Matrix.Column[3].W;
}

Matrix4x4 Matrix4x4::Tansponed() const
{
    Matrix4x4 Matrix;

    Matrix.Column[0].X = Column[0].X;
    Matrix.Column[1].X = Column[0].Y;
    Matrix.Column[2].X = Column[0].Z;
    Matrix.Column[3].X = Column[0].W;

    Matrix.Column[0].Y = Column[1].X;
    Matrix.Column[1].Y = Column[1].Y;
    Matrix.Column[2].Y = Column[1].Z;
    Matrix.Column[3].Y = Column[1].W;

    Matrix.Column[0].Z = Column[2].X;
    Matrix.Column[1].Z = Column[2].Y;
    Matrix.Column[2].Z = Column[2].Z;
    Matrix.Column[3].Z = Column[2].W;

    Matrix.Column[0].W = Column[3].X;
    Matrix.Column[1].W = Column[3].Y;
    Matrix.Column[2].W = Column[3].Z;
    Matrix.Column[3].W = Column[3].W;

    return Matrix;
}

Matrix4x4 Matrix4x4::Inverted() const
{
    float m[16] = {
        Column[0].X, Column[0].Y, Column[0].Z, Column[0].W,
        Column[1].X, Column[1].Y, Column[1].Z, Column[1].W,
        Column[2].X, Column[2].Y, Column[2].Z, Column[2].W,
        Column[3].X, Column[3].Y, Column[3].Z, Column[3].W,
    };

    float inv[16], det;
    int i = 0;

    inv[0] = m[5] * m[10] * m[15] -
        m[5] * m[11] * m[14] -
        m[9] * m[6] * m[15] +
        m[9] * m[7] * m[14] +
        m[13] * m[6] * m[11] -
        m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] +
        m[4] * m[11] * m[14] +
        m[8] * m[6] * m[15] -
        m[8] * m[7] * m[14] -
        m[12] * m[6] * m[11] +
        m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] -
        m[4] * m[11] * m[13] -
        m[8] * m[5] * m[15] +
        m[8] * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] +
        m[4] * m[10] * m[13] +
        m[8] * m[5] * m[14] -
        m[8] * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0.0f)
        return Matrix4x4::Identity();

    det = 1.0f / det;
    for (int i = 0; i < 16; i++)
        inv[i] *= det;

    Matrix4x4 invMat;
    invMat.Column[0].X = inv[0];
    invMat.Column[0].Y = inv[1];
    invMat.Column[0].Z = inv[2];
    invMat.Column[0].W = inv[3];

    invMat.Column[1].X = inv[4];
    invMat.Column[1].Y = inv[5];
    invMat.Column[1].Z = inv[6];
    invMat.Column[1].W = inv[7];

    invMat.Column[2].X = inv[8];
    invMat.Column[2].Y = inv[9];
    invMat.Column[2].Z = inv[10];
    invMat.Column[2].W = inv[11];

    invMat.Column[3].X = inv[12];
    invMat.Column[3].Y = inv[13];
    invMat.Column[3].Z = inv[14];
    invMat.Column[3].W = inv[15];

    return invMat;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& Other)
{
    Column[0] += Other.Column[0];
    Column[1] += Other.Column[1];
    Column[2] += Other.Column[2];
    Column[3] += Other.Column[3];
    return *this;
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& Other)
{
    Column[0] -= Other.Column[0];
    Column[1] -= Other.Column[1];
    Column[2] -= Other.Column[2];
    Column[3] -= Other.Column[3];
    return *this;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& Other)
{
    Matrix4x4 result = *this * Other;
    *this = result;
    return *this;
}

Matrix4x4& Matrix4x4::operator*=(float Scalar)
{
    Column[0] *= Scalar;
    Column[1] *= Scalar;
    Column[2] *= Scalar;
    Column[3] *= Scalar;
    return *this;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& Other) const
{
    Matrix4x4 result;
    result.Column[0] = Column[0] + Other.Column[0];
    result.Column[1] = Column[1] + Other.Column[1];
    result.Column[2] = Column[2] + Other.Column[2];
    result.Column[3] = Column[3] + Other.Column[3];
    return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& Other) const
{
    Matrix4x4 result;
    result.Column[0] = Column[0] - Other.Column[0];
    result.Column[1] = Column[1] - Other.Column[1];
    result.Column[2] = Column[2] - Other.Column[2];
    result.Column[3] = Column[3] - Other.Column[3];
    return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& Other) const
{
    Matrix4x4 Matrix;

    Matrix.Column[0].X = Column[0].X * Other.Column[0].X + Column[1].X * Other.Column[0].Y + Column[2].X * Other.Column[0].Z + Column[3].X * Other.Column[0].W;
    Matrix.Column[0].Y = Column[0].Y * Other.Column[0].X + Column[1].Y * Other.Column[0].Y + Column[2].Y * Other.Column[0].Z + Column[3].Y * Other.Column[0].W;
    Matrix.Column[0].Z = Column[0].Z * Other.Column[0].X + Column[1].Z * Other.Column[0].Y + Column[2].Z * Other.Column[0].Z + Column[3].Z * Other.Column[0].W;
    Matrix.Column[0].W = Column[0].W * Other.Column[0].X + Column[1].W * Other.Column[0].Y + Column[2].W * Other.Column[0].Z + Column[3].W * Other.Column[0].W;

    Matrix.Column[1].X = Column[0].X * Other.Column[1].X + Column[1].X * Other.Column[1].Y + Column[2].X * Other.Column[1].Z + Column[3].X * Other.Column[1].W;
    Matrix.Column[1].Y = Column[0].Y * Other.Column[1].X + Column[1].Y * Other.Column[1].Y + Column[2].Y * Other.Column[1].Z + Column[3].Y * Other.Column[1].W;
    Matrix.Column[1].Z = Column[0].Z * Other.Column[1].X + Column[1].Z * Other.Column[1].Y + Column[2].Z * Other.Column[1].Z + Column[3].Z * Other.Column[1].W;
    Matrix.Column[1].W = Column[0].W * Other.Column[1].X + Column[1].W * Other.Column[1].Y + Column[2].W * Other.Column[1].Z + Column[3].W * Other.Column[1].W;

    Matrix.Column[2].X = Column[0].X * Other.Column[2].X + Column[1].X * Other.Column[2].Y + Column[2].X * Other.Column[2].Z + Column[3].X * Other.Column[2].W;
    Matrix.Column[2].Y = Column[0].Y * Other.Column[2].X + Column[1].Y * Other.Column[2].Y + Column[2].Y * Other.Column[2].Z + Column[3].Y * Other.Column[2].W;
    Matrix.Column[2].Z = Column[0].Z * Other.Column[2].X + Column[1].Z * Other.Column[2].Y + Column[2].Z * Other.Column[2].Z + Column[3].Z * Other.Column[2].W;
    Matrix.Column[2].W = Column[0].W * Other.Column[2].X + Column[1].W * Other.Column[2].Y + Column[2].W * Other.Column[2].Z + Column[3].W * Other.Column[2].W;

    Matrix.Column[3].X = Column[0].X * Other.Column[3].X + Column[1].X * Other.Column[3].Y + Column[2].X * Other.Column[3].Z + Column[3].X * Other.Column[3].W;
    Matrix.Column[3].Y = Column[0].Y * Other.Column[3].X + Column[1].Y * Other.Column[3].Y + Column[2].Y * Other.Column[3].Z + Column[3].Y * Other.Column[3].W;
    Matrix.Column[3].Z = Column[0].Z * Other.Column[3].X + Column[1].Z * Other.Column[3].Y + Column[2].Z * Other.Column[3].Z + Column[3].Z * Other.Column[3].W;
    Matrix.Column[3].W = Column[0].W * Other.Column[3].X + Column[1].W * Other.Column[3].Y + Column[2].W * Other.Column[3].Z + Column[3].W * Other.Column[3].W;

    return Matrix;
}

Float4 Matrix4x4::operator*(const Float4& Other) const
{
    float x = Other.X * Column[0].X + Other.Y * Column[1].X + Other.Z * Column[2].X + Other.W * Column[3].X;
    float y = Other.X * Column[0].Y + Other.Y * Column[1].Y + Other.Z * Column[2].Y + Other.W * Column[3].Y;
    float z = Other.X * Column[0].Z + Other.Y * Column[1].Z + Other.Z * Column[2].Z + Other.W * Column[3].Z;
    float w = Other.X * Column[0].W + Other.Y * Column[1].W + Other.Z * Column[2].W + Other.W * Column[3].W;

    return { x, y, z, w };
}

Matrix4x4 Matrix4x4::operator*(float Scalar) const
{
    Matrix4x4 result;
    result.Column[0] *= Scalar;
    result.Column[1] *= Scalar;
    result.Column[2] *= Scalar;
    result.Column[3] *= Scalar;
    return result;
}

void Matrix4x4::Translate(Matrix4x4& Matrix, const Float3& translation)
{
    Matrix.Column[3].X += translation.X;
    Matrix.Column[3].Y += translation.Y;
    Matrix.Column[3].Z += translation.Z;
}

void Matrix4x4::Scale(Matrix4x4& Matrix, const Float3& Scale)
{
    Matrix.Column[0].X = Scale.X;
    Matrix.Column[1].Y = Scale.Y;
    Matrix.Column[2].Z = Scale.Z;
}

void Matrix4x4::RotateX(Matrix4x4& Matrix, float Radians)
{
    float a = Matrix.Column[0].Y;
    float b = Matrix.Column[0].Z;
    Matrix.Column[0].Y = a * cosf(Radians) - b * sinf(Radians);
    Matrix.Column[0].Z = a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[1].Y;
    b = Matrix.Column[1].Z;
    Matrix.Column[1].Y = a * cosf(Radians) - b * sinf(Radians);
    Matrix.Column[1].Z = a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[2].Y;
    b = Matrix.Column[2].Z;
    Matrix.Column[2].Y = a * cosf(Radians) - b * sinf(Radians);
    Matrix.Column[2].Z = a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[3].Y;
    b = Matrix.Column[3].Z;
    Matrix.Column[3].Y = a * cosf(Radians) - b * sinf(Radians);
    Matrix.Column[3].Z = a * sinf(Radians) + b * cosf(Radians);
}

void Matrix4x4::RotateY(Matrix4x4& Matrix, float Radians)
{
    float a = Matrix.Column[0].X;
    float b = Matrix.Column[0].Z;
    Matrix.Column[0].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[0].Z = -a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[1].X;
    b = Matrix.Column[1].Z;
    Matrix.Column[1].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[1].Z = -a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[2].X;
    b = Matrix.Column[2].Z;
    Matrix.Column[2].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[2].Z = -a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[3].X;
    b = Matrix.Column[3].Z;
    Matrix.Column[3].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[3].Z = -a * sinf(Radians) + b * cosf(Radians);
}

void Matrix4x4::RotateZ(Matrix4x4& Matrix, float Radians)
{
    float a = Matrix.Column[0].X;
    float b = Matrix.Column[0].Y;
    Matrix.Column[0].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[0].Y = -a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[1].X;
    b = Matrix.Column[1].Y;
    Matrix.Column[1].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[1].Y = -a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[2].X;
    b = Matrix.Column[2].Y;
    Matrix.Column[2].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[2].Y = -a * sinf(Radians) + b * cosf(Radians);
    a = Matrix.Column[3].X;
    b = Matrix.Column[3].Y;
    Matrix.Column[3].X = a * cosf(Radians) + b * sinf(Radians);
    Matrix.Column[3].Y = -a * sinf(Radians) + b * cosf(Radians);
}

void Matrix4x4::RotateXYZ(Matrix4x4& Matrix, const Float3& Rotation)
{
    if (Rotation.X != 0.0f)
        RotateX(Matrix, Rotation.X);
    if (Rotation.Y != 0.0f)
        RotateY(Matrix, Rotation.Y);
    if (Rotation.Z != 0.0f)
        RotateZ(Matrix, Rotation.Z);
}

Matrix4x4 Matrix4x4::Rotation(const Quaternion& Rotation)
{
    Matrix4x4 Matrix;

    Matrix.Column[0].X = 1.0f - 2.0f * (powf(Rotation.Y, 2.0f) + powf(Rotation.Z, 2.0f));
    Matrix.Column[0].Y = 2.0f * (Rotation.X * Rotation.Y + Rotation.W * Rotation.Z);
    Matrix.Column[0].Z = 2.0f * (Rotation.Z * Rotation.X - Rotation.W * Rotation.Y);
    Matrix.Column[0].W = 0.0f;

    Matrix.Column[1].X = 2.0f * (Rotation.X * Rotation.Y - Rotation.Z * Rotation.W);
    Matrix.Column[1].Y = 1.0f - 2.0f * (powf(Rotation.X, 2.0f) + powf(Rotation.Z, 2.0f));
    Matrix.Column[1].Z = 2.0f * (Rotation.Y * Rotation.Z + Rotation.W * Rotation.X);
    Matrix.Column[1].W = 0.0f;

    Matrix.Column[2].X = 2.0f * (Rotation.X * Rotation.Z + Rotation.Y * Rotation.W);
    Matrix.Column[2].Y = 2.0f * (Rotation.Y * Rotation.Z - Rotation.W * Rotation.X);
    Matrix.Column[2].Z = 1.0f - 2.0f * (powf(Rotation.X, 2.0f) + powf(Rotation.Y, 2.0f));
    Matrix.Column[2].W = 0.0f;

    Matrix.Column[3].X = 0.0f;
    Matrix.Column[3].Y = 0.0f;
    Matrix.Column[3].Z = 0.0f;
    Matrix.Column[3].W = 1.0f;

    return Matrix;
}

Matrix4x4 Matrix4x4::TRS(const Float3& Position, const Float3& Rotation, const Float3& Scale)
{
    Matrix4x4 Matrix;

    float cosx = cosf(Rotation.X);
    float sinx = sinf(Rotation.X);
    float cosy = cosf(Rotation.Y);
    float siny = sinf(Rotation.Y);
    float cosz = cosf(Rotation.Z);
    float sinz = sinf(Rotation.Z);

    Matrix.Column[0].X = Scale.X * cosy * cosz;
    Matrix.Column[0].Y = Scale.X * cosx * sinz;
    Matrix.Column[0].Z = Scale.X * (-siny);
    Matrix.Column[0].W = 0.0f;

    Matrix.Column[1].X = Scale.Y * (sinx * siny * cosz - cosx * sinz);
    Matrix.Column[1].Y = Scale.Y * (sinx * siny * sinz + cosx * cosz);
    Matrix.Column[1].Z = Scale.Y * sinx * cosy;
    Matrix.Column[1].W = 0.0f;

    Matrix.Column[2].X = Scale.Z * (cosx * siny * cosz + sinx * sinz);
    Matrix.Column[2].Y = Scale.Z * (cosx * siny * sinz - sinx * cosz);
    Matrix.Column[2].Z = Scale.Z * cosx * cosy;
    Matrix.Column[2].W = 0.0f;

    Matrix.Column[3].X = Position.X;
    Matrix.Column[3].Y = Position.Y;
    Matrix.Column[3].Z = Position.Z;
    Matrix.Column[3].W = 1.0f;

    return Matrix;
}

Matrix4x4 Matrix4x4::TRS(const Float3& Position, const Quaternion& Rotation, const Float3& Scale)
{
    Matrix4x4 Matrix;

    Matrix.Column[0].X = Scale.X * (1.0f - 2.0f * (powf(Rotation.Z, 2.0f) + powf(Rotation.Y, 2.0f)));
    Matrix.Column[0].Y = Scale.X * (2.0f * (Rotation.X * Rotation.Y + Rotation.W * Rotation.Z));
    Matrix.Column[0].Z = Scale.X * (2.0f * (Rotation.Z * Rotation.X - Rotation.W * Rotation.Y));
    Matrix.Column[0].W = 0.0f;

    Matrix.Column[1].X = Scale.Y * (2.0f * (Rotation.X * Rotation.Y - Rotation.W * Rotation.Z));
    Matrix.Column[1].Y = Scale.Y * (1.0f - 2.0f * (powf(Rotation.X, 2.0f) + powf(Rotation.Z, 2.0f)));
    Matrix.Column[1].Z = Scale.Y * (2.0f * (Rotation.Y * Rotation.Z + Rotation.W * Rotation.X));
    Matrix.Column[1].W = 0.0f;

    Matrix.Column[2].X = Scale.Z * (2.0f * (Rotation.Z * Rotation.X + Rotation.W * Rotation.Y));
    Matrix.Column[2].Y = Scale.Z * (2.0f * (Rotation.Y * Rotation.Z - Rotation.W * Rotation.X));
    Matrix.Column[2].Z = Scale.Z * (1.0f - 2.0f * (powf(Rotation.X, 2.0f) + powf(Rotation.Y, 2.0f)));
    Matrix.Column[2].W = 0.0f;

    Matrix.Column[3].X = Position.X;
    Matrix.Column[3].Y = Position.Y;
    Matrix.Column[3].Z = Position.Z;
    Matrix.Column[3].W = 1.0f;

    return Matrix;
}

Matrix4x4 Matrix4x4::PixelScreenMatrix(const Int2& Size, float Near, float Far)
{
    Matrix4x4 Matrix = Matrix4x4::Identity();
    Matrix.Column[0].X = 2.0f / Size.X;
    Matrix.Column[1].Y = -2.0f / Size.Y;
    Matrix.Column[2].Z = 1.0f;
    Matrix.Column[3].X = -1;
    Matrix.Column[3].Y = 1;
    Matrix.Column[3].Z = 0.0f;
    Matrix.Column[3].W = 1;
    return Matrix;
}

Matrix4x4 Matrix4x4::ProjectionMatrix(const Int2& Size, float FOV, float Near, float Far)
{
    float aspectRatio = (float)Size.X / (float)Size.Y;
    float tg = tanf(FOV * 0.5f * PI / 180.0f);

    Matrix4x4 Matrix = Matrix4x4::Identity();

    Matrix.Column[0].X = 1.0f / (aspectRatio * tg);
    Matrix.Column[1].Y = 1.0f / tg;
    Matrix.Column[2].Z = (-Far - Near) / (Far - Near);
    Matrix.Column[2].W = -1.0f;
    Matrix.Column[3].Z = (-Far * Near) / (Far - Near);
    Matrix.Column[3].W = 0.0f;

    return Matrix;
}

Matrix4x4 Matrix4x4::LookAtMatrix(const Float3& Eye, const Float3& Target, const Float3& UpVector)
{
    Float3 f = Target - Eye;
    f.Normalize();
    f *= -1.0f;

    Float3 r = UpVector.CrossProduct(f);
    r.Normalize();
    r *= -1.0f;

    Float3 u = f.CrossProduct(r);
    u.Normalize();
    u *= -1.0f;

    Matrix4x4 Matrix;

    Matrix.Column[0].X = r.X;
    Matrix.Column[1].X = r.Y;
    Matrix.Column[2].X = r.Z;

    Matrix.Column[0].Y = u.X;
    Matrix.Column[1].Y = u.Y;
    Matrix.Column[2].Y = u.Z;

    Matrix.Column[0].Z = f.X;
    Matrix.Column[1].Z = f.Y;
    Matrix.Column[2].Z = f.Z;

    Matrix.Column[0].W = 0.0f;
    Matrix.Column[1].W = 0.0f;
    Matrix.Column[2].W = 0.0f;

    Matrix.Column[3].X = -r.DotProduct(Eye);
    Matrix.Column[3].Y = -u.DotProduct(Eye);
    Matrix.Column[3].Z = -f.DotProduct(Eye);
    Matrix.Column[3].W = 1.0f;

    return Matrix;
}

Matrix4x4 Matrix4x4::OrthographicMatrix(const Int2& Size, float Near, float Far)
{
    Matrix4x4 Matrix = Matrix4x4::Identity();
    Matrix.Column[0].X = 2.0f / Size.X;
    Matrix.Column[1].Y = -2.0f / Size.Y;
    Matrix.Column[2].Z = -2.0f / (Far - Near);
    Matrix.Column[3].X = -1;
    Matrix.Column[3].Y = 1;
    Matrix.Column[3].Z = (Far + Near) / (Far - Near);
    Matrix.Column[3].W = 1;
    return Matrix;
}