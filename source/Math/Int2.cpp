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

void Int2::operator+=(const Int2& Other)
{
    X += Other.X;
    Y += Other.Y;
}

void Int2::operator-=(const Int2& Other)
{
    X -= Other.X;
    Y -= Other.Y;
}

bool Int2::operator==(const Int2& Other)
{
    return X == Other.X && Y == Other.Y;
}

bool Int2::operator!=(const Int2& Other)
{
    return !(*this == Other);
}

Int2 Int2::operator+(const Int2& Other)
{
    return { X + Other.X, Y + Other.Y };
}

Int2 Int2::operator-(const Int2& Other)
{
    return { X - Other.X, Y - Other.Y };
}

int Int2::DotProduct(const Int2& Other)
{
    return (X * Other.X) + (Y * Other.Y);
}

float Int2::Distance(const Int2& Other)
{
    float X2 = (float)((X - Other.X) * (X - Other.X));
    float Y2 = (float)((Y - Other.Y) * (Y - Other.Y));
    return sqrtf(X2 + Y2);
}