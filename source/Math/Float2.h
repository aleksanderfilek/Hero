#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"
#include <iostream>

struct HERO_API Float2
{
    float X, Y;

    constexpr Float2() : X(0.0f), Y(0.0f) {}
    constexpr Float2(float X, float Y) : X(X), Y(Y) {}
    Float2(const Float2& Other);
    Float2(const String& Str);

    constexpr static inline Float2 Zero() { return Float2(0.0f, 0.0f); }
    constexpr static inline Float2 One()  { return Float2(1.0f, 1.0f); }
    constexpr static inline Float2 Right(){ return Float2(1.0f, 0.0f); }
    constexpr static inline Float2 Up()   { return Float2(0.0f, 1.0f); }

    float Length() const;

    Float2& operator+=(const Float2& Other);
    Float2& operator-=(const Float2& Other);
    Float2& operator*=(float Scalar);
    Float2& operator/=(float Scalar);

    Float2 operator+(const Float2& Other);
    Float2 operator-(const Float2& Other);
    Float2 operator*(float Scalar);
    Float2 operator/(float Scalar);

    bool operator==(const Float2& Other) const;
    bool operator!=(const Float2& Other) const;

    float DotProduct(const Float2& Other) const;
    float CrossProduct(const Float2& Other) const;

    float DistanceSquared(const Float2& Other) const;
    float Distance(const Float2& Other) const;

    friend std::ostream& operator<<(std::ostream& Stream, const Float2& Value)
    {
        Stream << "{" << Value.X << "," << Value.Y << "}";
        return Stream;
    }
};
