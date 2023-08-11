#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"
#include <iostream>

struct HERO_API Int2
{
    int X, Y;

    constexpr Int2() : X(0), Y(0) {}
    constexpr Int2(int X, int Y) : X(X), Y(Y) {}
    Int2(const Int2& Other);
    Int2(const String& Str);

    constexpr static inline Int2 Zero() { return Int2(0, 0); }
    constexpr static inline Int2 One()  { return Int2(1, 1); }
    constexpr static inline Int2 Right(){ return Int2(1, 0); }
    constexpr static inline Int2 Up()   { return Int2(0, 1); }

    float Length() const;

    Int2& operator+=(const Int2& Other);
    Int2& operator-=(const Int2& Other);
    Int2& operator*=(int Scalar);
    Int2& operator/=(int Scalar);

    Int2 operator+(const Int2& Other);
    Int2 operator-(const Int2& Other);
    Int2 operator*(int Scalar);
    Int2 operator/(int Scalar);

    bool operator==(const Int2& Other) const;
    bool operator!=(const Int2& Other) const;

    int DotProduct(const Int2& Other) const;
    int CrossProduct(const Int2& Other) const;

    float DistanceSquared(const Int2& Other) const;
    float Distance(const Int2& Other) const;

    friend std::ostream& operator<<(std::ostream& Stream, const Int2& Value)
    {
        Stream << "{" << Value.X << "," << Value.Y << "}";
        return Stream;
    }
};
