#include "Float3.h"
#include <cmath>
#include <cstdio>
#include "MathConstants.h"

Float3::Float3(const Float3& Other)
{
    X = Other.X;
    Y = Other.Y;
    Z = Other.Z;
}

Float3::Float3(const String& Str)
{
    sscanf(*const_cast<String&>(Str), "{%f,%f,%f}", &X, &Y, &Z);
}

float Float3::Length() const
{
    return sqrtf(powf(X, 2.0f) + powf(Y, 2.0f) + powf(Z, 2.0f));
}

Float3& Float3::operator+=(const Float3& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    return *this;
}

Float3& Float3::operator-=(const Float3& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    Z -= Other.Z;
    return *this;
}

Float3& Float3::operator*=(float Scalar)
{
    X *= Scalar;
    Y *= Scalar;
    Z *= Scalar;
    return *this;
}

Float3& Float3::operator/=(float Scalar)
{
    X /= Scalar;
    Y /= Scalar;
    Z /= Scalar;
    return *this;
}

Float3 Float3::operator+(const Float3& Other)
{
    return { X + Other.X, Y + Other.Y, Z + Other.Z };
}

Float3 Float3::operator-(const Float3& Other)
{
    return { X - Other.X, Y - Other.Y, Z - Other.Z };
}

Float3 Float3::operator*(float Scalar)
{
    return { X * Scalar, Y * Scalar, Z * Scalar };
}

Float3 Float3::operator/(float Scalar)
{
    return { X / Scalar, Y / Scalar, Z / Scalar };
}

bool Float3::operator==(const Float3& Other) const
{
    return fabsf(X == Other.X) < EPSILON && 
            fabsf(Y == Other.Y) < EPSILON && 
            fabsf(Z == Other.Z) < EPSILON;
}

bool Float3::operator!=(const Float3& Other) const
{
    return !(*this == Other);
}

float Float3::DotProduct(const Float3& Other) const
{
    return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
}

Float3 Float3::CrossProduct(const Float3& Other) const
{
    float x = Y * Other.Z - Z * Other.Y;
    float y = Z * Other.X - X * Other.Z;
    float z = X * Other.Y - Y * Other.X;
    return { x, y, z };
}

float Float3::DistanceSquared(const Float3& Other) const
{
    float x2 = ((X - Other.X) * (X - Other.X));
    float y2 = ((Y - Other.Y) * (Y - Other.Y));
    float z2 = ((Z - Other.Z) * (Z - Other.Z));
    return x2 + y2 + z2;
}

float Float3::Distance(const Float3& Other) const
{
    return sqrtf(DistanceSquared(Other));
}

Float3 Float3::Lerp(const Float3& From, const Float3& To, float Alpha)
{
    float x = (1.0f - Alpha) * From.X + Alpha * To.X;
    float y = (1.0f - Alpha) * From.Y + Alpha * To.Y;
    float z = (1.0f - Alpha) * From.Z + Alpha * To.Z;
    return { x, y, z };    
}