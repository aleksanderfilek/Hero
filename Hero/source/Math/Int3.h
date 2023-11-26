#pragma once

#include "../Definitions.h"
#include <iostream>

struct HERO_API Int3
{
    int X, Y, Z;

    constexpr Int3() : X(0), Y(0), Z(0) {}
    constexpr Int3(int X, int Y, int Z) : X(X), Y(Y), Z(Z) {}
    Int3(const Int3& Other);
    Int3(const char* Str);

    constexpr static inline Int3 Zero()     { return Int3(0, 0, 0); }
    constexpr static inline Int3 One()      { return Int3(1, 1, 1); }
    constexpr static inline Int3 Forward()  { return Int3(0, 1, 0); }
    constexpr static inline Int3 Right()    { return Int3(1, 0, 0); }
    constexpr static inline Int3 Up()       { return Int3(0, 0, 1); }

    float Length() const;

    Int3& operator+=(const Int3& Other);
    Int3& operator-=(const Int3& Other);
    Int3& operator*=(int Scalar);
    Int3& operator/=(int Scalar);

    Int3 operator+(const Int3& Other) const;
    Int3 operator-(const Int3& Other) const;
    Int3 operator*(int Scalar) const;
    Int3 operator/(int Scalar) const;

    bool operator==(const Int3& Other) const;
    bool operator!=(const Int3& Other) const;

    int DotProduct(const Int3& Other) const;
    Int3 CrossProduct(const Int3& Other) const;
    
    float DistanceSquared(const Int3& Other) const;
    float Distance(const Int3& Other) const;

    friend std::ostream& operator<<(std::ostream& Stream, const Int3& Value)
    {
        Stream << "{" << Value.X << "," << Value.Y<< "," << Value.Z << "}";
        return Stream;
    }

    static Int3 Lerp(const Int3& From, const Int3& To, float Alpha);
};