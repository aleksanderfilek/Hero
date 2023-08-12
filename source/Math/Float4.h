#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"
#include <iostream>

struct HERO_API Float4
{
    float X, Y, Z, W;

    constexpr Float4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
    constexpr Float4(float X, float Y, float Z, float W) : X(X), Y(Y), Z(Z), W(W) {}
    Float4(const Float4& Other);
    Float4(const String& Str);

    constexpr static inline Float4 Zero()     { return Float4(0.0f, 0.0f, 0.0f, 0.0f); }
    constexpr static inline Float4 One()      { return Float4(1.0f, 1.0f, 1.0f, 1.0f); }

    float Length() const;

    Float4& operator+=(const Float4& Other);
    Float4& operator-=(const Float4& Other);
    Float4& operator*=(float Scalar);
    Float4& operator/=(float Scalar);

    Float4 operator+(const Float4& Other);
    Float4 operator-(const Float4& Other);
    Float4 operator*(float Scalar);
    Float4 operator/(float Scalar);

    bool operator==(const Float4& Other) const;
    bool operator!=(const Float4& Other) const;

    float DotProduct(const Float4& Other) const;
    float DistanceSquared(const Float4& Other) const;
    float Distance(const Float4& Other) const;

    friend std::ostream& operator<<(std::ostream& Stream, const Float4& Value)
    {
        Stream << "{" << Value.X << "," << Value.Y<< "," << Value.Z<< "," << Value.W << "}";
        return Stream;
    }

    static Float4 Lerp(const Float4& From, const Float4& To, float Alpha);
};