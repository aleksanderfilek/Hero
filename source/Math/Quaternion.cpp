#include "Quaternion.h"
#include <cmath>
#include <cstdio>
#include "MathConstants.h"

Quaternion::Quaternion(float rotX, float rotY, float rotZ)
{
    double cY = cosf(rotZ * 0.5f);
    double sY = sinf(rotZ * 0.5f);
    double cp = cosf(rotX * 0.5f);
    double sp = sinf(rotX * 0.5f);
    double cr = cosf(rotY * 0.5f);
    double sr = sinf(rotY * 0.5f);

    W = (float)(cr * cp * cY + sr * sp * sY);
    X = (float)(sr * cp * cY - cr * sp * sY);
    Y = (float)(cr * sp * cY + sr * cp * sY);
    Z = (float)(cr * cp * sY - sr * sp * cY);
}

Quaternion::Quaternion(const Float3& vector)
{
    double cY = cos(vector.X * 0.5);
    double sY = sin(vector.X * 0.5);
    double cp = cos(vector.Y * 0.5);
    double sp = sin(vector.Y * 0.5);
    double cr = cos(vector.Z * 0.5);
    double sr = sin(vector.Z * 0.5);

    W = (float)(cr * cp * cY + sr * sp * sY);
    X = (float)(sr * cp * cY - cr * sp * sY);
    Y = (float)(cr * sp * cY + sr * cp * sY);
    Z = (float)(cr * cp * sY - sr * sp * cY);
}

Quaternion::Quaternion(float angle, const Float3& aXis)
{
    W = cosf(angle * 0.5f);
    X = sinf(angle * 0.5f) * aXis.X;
    Y = sinf(angle * 0.5f) * aXis.Y;
    Z = sinf(angle * 0.5f) * aXis.Z;
}

Quaternion::Quaternion(const String& Str)
{
    sscanf(*const_cast<String&>(Str), "{%f,%f,%f,%f}", &W, &X, &Y, &Z);
}

Float3 Quaternion::GetForwardVector() const
{
    return *this * Float3::Forward();
}

Float3 Quaternion::GetRightVector() const
{
    return *this * Float3::Right();
}

Float3 Quaternion::GetUpVector() const
{
    return *this * Float3::Up();
}

Float3 Quaternion::ToEuler() const
{
    Float3 result;

    // roll
    double sinr_cosp = 2 * (W * Z + X * Y);
    double cosr_cosp = 1 - 2 * (Z * Z + X * X);
    result.Z = (float)std::atan2(sinr_cosp, cosr_cosp);

    // pitch (Y-aXis rotation)
    double sinp = 2 * (W * X - Y * Z);
    if (std::abs(sinp) >= 1)
        result.X = (float)std::copysign(PI / 2, sinp); // use 90 degrees if out of range
    else
        result.X = (float)std::asin(sinp);

    // YaW (Z-aXis rotation)
    double sinY_cosp = 2 * (W * Y + Z * X);
    double cosY_cosp = 1 - 2 * (X * X + Y * Y);
    result.Y = (float)std::atan2(sinY_cosp, cosY_cosp);

    return result;
}

Quaternion& Quaternion::operator+=(const Quaternion& Other)
{
    W += Other.W;
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& Other)
{
    W -= Other.W;
    X -= Other.X;
    Y -= Other.Y;
    Z -= Other.Z;
    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& Other)
{
    W = W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z;
    X = W * Other.X + X * Other.W + Y * Other.Z - Z * Other.Y;
    Y = W * Other.Y - X * Other.Z + Y * Other.W + Z * Other.X;
    Z = W * Other.Z + X * Other.Y - Y * Other.X + Z * Other.W;
    return *this;
}

bool Quaternion::operator==(const Quaternion& Other) const
{
    return W == Other.W && X == Other.X && Y == Other.Y && Z == Other.Z;
}

bool Quaternion::operator!=(const Quaternion& Other) const
{
    return W != Other.W && X != Other.X && Y != Other.Y && Z != Other.Z;
}

Quaternion Quaternion::operator~() const
{
    Quaternion q;
    q.W = (*this).W;
    q.X = -(*this).X;
    q.Y = -(*this).Y;
    q.Z = -(*this).Z;
    return q;
}

Quaternion Quaternion::operator+(const Quaternion& Other) const
{
    Quaternion q;
    q.W = W + Other.W;
    q.X = X + Other.X;
    q.Y = Y + Other.W;
    q.Z = Z + Other.Z;
    return q;
}

Quaternion Quaternion::operator-(const Quaternion& Other) const
{
    Quaternion q;
    q.W = W - Other.W;
    q.X = X - Other.X;
    q.Y = Y - Other.W;
    q.Z = Z - Other.Z;
    return q;
}

Quaternion Quaternion::operator*(const Quaternion& Other) const
{
    Quaternion q;
    q.W = W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z;
    q.X = W * Other.X + X * Other.W + Y * Other.Z - Z * Other.Y;
    q.Y = W * Other.Y - X * Other.Z + Y * Other.W + Z * Other.X;
    q.Z = W * Other.Z + X * Other.Y - Y * Other.X + Z * Other.W;
    return q;
}

Float3 Quaternion::operator*(const Float3& Other) const
{
    Quaternion q = *this;
    Quaternion lhs2 = ~(*this);

    q *= Other;
    q *= lhs2;

    return Float3(q.X, q.Y, q.Z);
}

// Float3 operator*(const Quaternion& lhs, const Float3& Other)
// {
//     Float3 u(X, Y, Z);

//     float s = W;

//     return 2.0f * dotProduct(u, Other) * u + 
//         (s*s - dotProduct(u,u)) * Other +
//         2.0f * s * crossProduct(u, v);
// }
