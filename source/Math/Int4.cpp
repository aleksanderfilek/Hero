#include "Int4.h"
#include <cmath>
#include <cstdio>

Int4::Int4(const Int4& Other)
{
    X = Other.X;
    Y = Other.Y;
    Z = Other.Z;
    W = Other.W;
}

Int4::Int4(const String& Str)
{
    sscanf(*const_cast<String&>(Str), "{%d,%d,%d,%d}", &X, &Y, &Z, &W);
}

float Int4::Length() const
{
    return sqrtf(powf((float)X, 2.0f) + powf((float)Y, 2.0f) + 
        powf((float)Z, 2.0f) + powf((float)W, 2.0f));
}

Int4& Int4::operator+=(const Int4& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    W += Other.W;
    return *this;
}

Int4& Int4::operator-=(const Int4& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    Z -= Other.Z;
    W -= Other.W;
    return *this;
}

Int4& Int4::operator*=(int Scalar)
{
    X *= Scalar;
    Y *= Scalar;
    Z *= Scalar;
    W *= Scalar;
    return *this;
}

Int4& Int4::operator/=(int Scalar)
{
    X /= Scalar;
    Y /= Scalar;
    Z /= Scalar;
    W /= Scalar;
    return *this;
}

Int4 Int4::operator+(const Int4& Other)
{
    return { X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W };
}

Int4 Int4::operator-(const Int4& Other)
{
    return { X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W };
}

Int4 Int4::operator*(int Scalar)
{
    return { X * Scalar, Y * Scalar, Z * Scalar, W * Scalar };
}

Int4 Int4::operator/(int Scalar)
{
    return { X / Scalar, Y / Scalar, Z / Scalar, W / Scalar };
}

bool Int4::operator==(const Int4& Other) const
{
    return X == Other.X && Y == Other.Y && Z == Other.Z && W == Other.W;
}

bool Int4::operator!=(const Int4& Other) const
{
    return !(*this == Other);
}

int Int4::DotProduct(const Int4& Other) const
{
    return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z) + (W * Other.W);
}

float Int4::DistanceSquared(const Int4& Other) const
{
    float x2 = (float)((X - Other.X) * (X - Other.X));
    float y2 = (float)((Y - Other.Y) * (Y - Other.Y));
    float z2 = (float)((Z - Other.Z) * (Z - Other.Z));
    float w2 = (float)((W - Other.W) * (W - Other.W));
    return x2 + y2 + z2 + w2;
}

float Int4::Distance(const Int4& Other) const
{
    return sqrtf(DistanceSquared(Other));
}