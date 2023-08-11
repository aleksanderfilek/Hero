#include "Int2.h"
#include <cmath>
#include <cstdio>

Int2::Int2(const Int2& Other)
{
    X = Other.X;
    Y = Other.Y;
}

Int2::Int2(const String& Str)
{
    sscanf(*const_cast<String&>(Str), "{%d,%d}", &X, &Y);
}

float Int2::Length() const
{
    return sqrtf(powf((float)X, 2.0f) + powf((float)Y, 2.0f));
}

Int2& Int2::operator+=(const Int2& Other)
{
    X += Other.X;
    Y += Other.Y;
    return *this;
}

Int2& Int2::operator-=(const Int2& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    return *this;
}

Int2& Int2::operator*=(int Scalar)
{
    X *= Scalar;
    Y *= Scalar;
    return *this;
}

Int2& Int2::operator/=(int Scalar)
{
    X /= Scalar;
    Y /= Scalar;
    return *this;
}

Int2 Int2::operator+(const Int2& Other)
{
    return { X + Other.X, Y + Other.Y };
}

Int2 Int2::operator-(const Int2& Other)
{
    return { X - Other.X, Y - Other.Y };
}

Int2 Int2::operator*(int Scalar)
{
    return { X * Scalar, Y * Scalar };
}

Int2 Int2::operator/(int Scalar)
{
    return { X / Scalar, Y / Scalar };
}

bool Int2::operator==(const Int2& Other) const
{
    return X == Other.X && Y == Other.Y;
}

bool Int2::operator!=(const Int2& Other) const
{
    return !(*this == Other);
}

int Int2::DotProduct(const Int2& Other) const
{
    return (X * Other.X) + (Y * Other.Y);
}

int Int2::CrossProduct(const Int2& Other) const
{
    return X * Other.Y - Y * Other.X;
}

float Int2::DistanceSquared(const Int2& Other) const
{
    float x2 = (float)((X - Other.X) * (X - Other.X));
    float y2 = (float)((Y - Other.Y) * (Y - Other.Y));
    return x2 + y2;
}

float Int2::Distance(const Int2& Other) const
{
    return sqrtf(DistanceSquared(Other));
}