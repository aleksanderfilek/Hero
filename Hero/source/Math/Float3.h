#pragma once

#include "../Definitions.h"
#include <iostream>

struct HERO_API Float3
{
    float X, Y, Z;

    constexpr Float3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    constexpr Float3(float X, float Y, float Z) : X(X), Y(Y), Z(Z) {}
    Float3(const Float3& Other);
    Float3(const char* Str);

    constexpr static inline Float3 Zero()     { return Float3(0.0f, 0.0f, 0.0f); }
    constexpr static inline Float3 One()      { return Float3(1.0f, 1.0f, 1.0f); }
    constexpr static inline Float3 Forward()  { return Float3(0.0f, 1.0f, 0.0f); }
    constexpr static inline Float3 Right()    { return Float3(1.0f, 0.0f, 0.0f); }
    constexpr static inline Float3 Up()       { return Float3(0.0f, 0.0f, 1.0f); }

    float Length() const;
    void Normalize();
    Float3 Normalized() const;

    Float3& operator+=(const Float3& Other);
    Float3& operator-=(const Float3& Other);
    Float3& operator*=(float Scalar);
    Float3& operator/=(float Scalar);

    Float3 operator+(const Float3& Other) const;
    Float3 operator-(const Float3& Other) const;
    Float3 operator*(float Scalar) const;
    Float3 operator/(float Scalar) const;

    bool operator==(const Float3& Other) const;
    bool operator!=(const Float3& Other) const;

    float DotProduct(const Float3& Other) const;
    Float3 CrossProduct(const Float3& Other) const;
    
    float DistanceSquared(const Float3& Other) const;
    float Distance(const Float3& Other) const;

    friend std::ostream& operator<<(std::ostream& Stream, const Float3& Value)
    {
        Stream << "{" << Value.X << "," << Value.Y<< "," << Value.Z << "}";
        return Stream;
    }

    static Float3 Lerp(const Float3& From, const Float3& To, float Alpha);
};