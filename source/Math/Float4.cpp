#include "Float4.h"
#include <cmath>
#include <cstdio>
#include "MathConstants.h"

Float4::Float4(const Float4& Other)
{
    X = Other.X;
    Y = Other.Y;
    Z = Other.Z;
    W = Other.W;
}

Float4::Float4(const String& Str)
{
    sscanf(*const_cast<String&>(Str), "{%d,%d,%d,%d}", &X, &Y, &Z, &W);
}

float Float4::Length() const
{
    return sqrtf(powf(X, 2.0f) + powf(Y, 2.0f) + 
        powf(Z, 2.0f) + powf(W, 2.0f));
}

Float4& Float4::operator+=(const Float4& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    W += Other.W;
    return *this;
}

Float4& Float4::operator-=(const Float4& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    Z -= Other.Z;
    W -= Other.W;
    return *this;
}

Float4& Float4::operator*=(float Scalar)
{
    X *= Scalar;
    Y *= Scalar;
    Z *= Scalar;
    W *= Scalar;
    return *this;
}

Float4& Float4::operator/=(float Scalar)
{
    X /= Scalar;
    Y /= Scalar;
    Z /= Scalar;
    W /= Scalar;
    return *this;
}

Float4 Float4::operator+(const Float4& Other)
{
    return { X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W };
}

Float4 Float4::operator-(const Float4& Other)
{
    return { X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W };
}

Float4 Float4::operator*(float Scalar)
{
    return { X * Scalar, Y * Scalar, Z * Scalar, W * Scalar };
}

Float4 Float4::operator/(float Scalar)
{
    return { X / Scalar, Y / Scalar, Z / Scalar, W / Scalar };
}

bool Float4::operator==(const Float4& Other) const
{
    return fabsf(X == Other.X) < EPSILON && 
            fabsf(Y == Other.Y) < EPSILON && 
            fabsf(Z == Other.Z) < EPSILON &&
            fabsf(W == Other.W) < EPSILON;
}

bool Float4::operator!=(const Float4& Other) const
{
    return !(*this == Other);
}

float Float4::DotProduct(const Float4& Other) const
{
    return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z) + (W * Other.W);
}

float Float4::DistanceSquared(const Float4& Other) const
{
    float x2 = ((X - Other.X) * (X - Other.X));
    float y2 = ((Y - Other.Y) * (Y - Other.Y));
    float z2 = ((Z - Other.Z) * (Z - Other.Z));
    float w2 = ((W - Other.W) * (W - Other.W));
    return x2 + y2 + z2 + w2;
}

float Float4::Distance(const Float4& Other) const
{
    return sqrtf(DistanceSquared(Other));
}