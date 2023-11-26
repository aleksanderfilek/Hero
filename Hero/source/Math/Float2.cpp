#include "Float2.h"
#include <cmath>
#include <cstdio>
#include "MathConstants.h"

Float2::Float2(const Float2& Other)
{
    X = Other.X;
    Y = Other.Y;
}

Float2::Float2(const char* Str)
{
    sscanf(Str, "{%f,%f}", &X, &Y);
}

float Float2::Length() const
{
    return sqrtf(powf(X, 2.0f) + powf(Y, 2.0f));
}

void Float2::Normalize()
{
    *this /= Length();
}

Float2 Float2::Normalized() const
{
    return *this / Length();
}

Float2& Float2::operator+=(const Float2& Other)
{
    X += Other.X;
    Y += Other.Y;
    return *this;
}

Float2& Float2::operator-=(const Float2& Other)
{
    X -= Other.X;
    Y -= Other.Y;
    return *this;
}

Float2& Float2::operator*=(float Scalar)
{
    X *= Scalar;
    Y *= Scalar;
    return *this;
}

Float2& Float2::operator/=(float Scalar)
{
    X /= Scalar;
    Y /= Scalar;
    return *this;
}

Float2 Float2::operator+(const Float2& Other) const
{
    return { X + Other.X, Y + Other.Y };
}

Float2 Float2::operator-(const Float2& Other) const
{
    return { X - Other.X, Y - Other.Y };
}

Float2 Float2::operator*(float Scalar) const
{
    return { X * Scalar, Y * Scalar };
}

Float2 Float2::operator/(float Scalar) const
{
    return { X / Scalar, Y / Scalar };
}

bool Float2::operator==(const Float2& Other) const
{
    return fabsf(X - Other.X) < EPSILON && fabsf(Y == Other.Y) < EPSILON;
}

bool Float2::operator!=(const Float2& Other) const
{
    return !(*this == Other);
}

float Float2::DotProduct(const Float2& Other) const
{
    return (X * Other.X) + (Y * Other.Y);
}

float Float2::CrossProduct(const Float2& Other) const
{
    return X * Other.Y - Y * Other.X;
}

float Float2::DistanceSquared(const Float2& Other) const
{
    float x2 = ((X - Other.X) * (X - Other.X));
    float y2 = ((Y - Other.Y) * (Y - Other.Y));
    return x2 + y2;
}

float Float2::Distance(const Float2& Other) const
{
    return sqrtf(DistanceSquared(Other));
}

Float2 Float2::Lerp(const Float2& From, const Float2& To, float Alpha)
{
    float x = (1.0f - Alpha) * From.X + Alpha * To.X;
    float y = (1.0f - Alpha) * From.Y + Alpha * To.Y;
    return { x, y };
}