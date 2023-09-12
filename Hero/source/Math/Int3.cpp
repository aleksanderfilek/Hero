#include "Int3.h"
#include <cmath>
#include <cstdio>

Int3::Int3(const Int3& Other)
{
    X = Other.X;
    Y = Other.Y;
    Z = Other.Z;
}

Int3::Int3(const String& Str)
{
    sscanf(*const_cast<String&>(Str), "{%d,%d,%d}", &X, &Y, &Z);
}

float Int3::Length() const
{
    return sqrtf(powf((float)X, 2.0f) + powf((float)Y, 2.0f) + powf((float)Z, 2.0f));
}

Int3& Int3::operator+=(const Int3& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    return *this;
}

Int3& Int3::operator-=(const Int3& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    Z -= Other.Z;
    return *this;
}

Int3& Int3::operator*=(int Scalar)
{
    X *= Scalar;
    Y *= Scalar;
    Z *= Scalar;
    return *this;
}

Int3& Int3::operator/=(int Scalar)
{
    X /= Scalar;
    Y /= Scalar;
    Z /= Scalar;
    return *this;
}

Int3 Int3::operator+(const Int3& Other) const
{
    return { X + Other.X, Y + Other.Y, Z + Other.Z };
}

Int3 Int3::operator-(const Int3& Other) const
{
    return { X - Other.X, Y - Other.Y, Z - Other.Z };
}

Int3 Int3::operator*(int Scalar) const
{
    return { X * Scalar, Y * Scalar, Z * Scalar };
}

Int3 Int3::operator/(int Scalar) const
{
    return { X / Scalar, Y / Scalar, Z / Scalar };
}

bool Int3::operator==(const Int3& Other) const
{
    return X == Other.X && Y == Other.Y && Z == Other.Z;
}

bool Int3::operator!=(const Int3& Other) const
{
    return !(*this == Other);
}

int Int3::DotProduct(const Int3& Other) const
{
    return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
}

Int3 Int3::CrossProduct(const Int3& Other) const
{
    int x = Y * Other.Z - Z * Other.Y;
    int y = Z * Other.X - X * Other.Z;
    int z = X * Other.Y - Y * Other.X;
    return { x, y, z };
}

float Int3::DistanceSquared(const Int3& Other) const
{
    float x2 = (float)((X - Other.X) * (X - Other.X));
    float y2 = (float)((Y - Other.Y) * (Y - Other.Y));
    float z2 = (float)((Z - Other.Z) * (Z - Other.Z));
    return x2 + y2 + z2;
}

float Int3::Distance(const Int3& Other) const
{
    return sqrtf(DistanceSquared(Other));
}

Int3 Int3::Lerp(const Int3& From, const Int3& To, float Alpha)
{
    int x = (1.0f - Alpha) * From.X + Alpha * To.X;
    int y = (1.0f - Alpha) * From.Y + Alpha * To.Y;
    int z = (1.0f - Alpha) * From.Z + Alpha * To.Z;
    return { x, y, z };    
}