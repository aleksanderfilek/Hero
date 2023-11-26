#pragma once

#include "../Definitions.h"
#include <iostream>

struct HERO_API Int4
{
    int X, Y, Z, W;

    constexpr Int4() : X(0), Y(0), Z(0), W(0) {}
    constexpr Int4(int X, int Y, int Z, int W) : X(X), Y(Y), Z(Z), W(W) {}
    Int4(const Int4& Other);
    Int4(const char* Str);

    constexpr static inline Int4 Zero()     { return Int4(0, 0, 0, 0); }
    constexpr static inline Int4 One()      { return Int4(1, 1, 1, 1); }

    float Length() const;

    Int4& operator+=(const Int4& Other);
    Int4& operator-=(const Int4& Other);
    Int4& operator*=(int Scalar);
    Int4& operator/=(int Scalar);

    Int4 operator+(const Int4& Other) const;
    Int4 operator-(const Int4& Other) const;
    Int4 operator*(int Scalar) const;
    Int4 operator/(int Scalar) const;

    bool operator==(const Int4& Other) const;
    bool operator!=(const Int4& Other) const;

    int DotProduct(const Int4& Other) const;
    float DistanceSquared(const Int4& Other) const;
    float Distance(const Int4& Other) const;

    friend std::ostream& operator<<(std::ostream& Stream, const Int4& Value)
    {
        Stream << "{" << Value.X << "," << Value.Y<< "," << Value.Z<< "," << Value.W << "}";
        return Stream;
    }

    static Int4 Lerp(const Int4& From, const Int4& To, float Alpha);
};