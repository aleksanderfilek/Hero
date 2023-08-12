#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"
#include "Float3.h"
#include <iostream>

struct HERO_API Quaternion
{
    float W, X, Y, Z;

    Quaternion() :W(1.0f), X(0.0f), Y(0.0f), Z(0.0f) {}
    Quaternion(float RotX, float RotY, float RotZ);
    Quaternion(const Float3& Vector);
    Quaternion(float Angle, const Float3& Axis);
    Quaternion(const String& Str);

    Float3 GetForwardVector() const;
    Float3 GetRightVector() const;
    Float3 GetUpVector() const;

    Float3 ToEuler() const;

    Quaternion& operator+=(const Quaternion& Other);
    Quaternion& operator-=(const Quaternion& Other);
    Quaternion& operator*=(const Quaternion& Other);
    bool operator==(const Quaternion& Other) const;
    bool operator!=(const Quaternion& Other) const;

    Quaternion operator~() const;
    Quaternion operator+(const Quaternion& Other) const;
    Quaternion operator-(const Quaternion& Other) const;
    Quaternion operator*(const Quaternion& Other) const;
    Float3 operator*(const Float3& rhOthers) const;

    friend std::ostream& operator<< (std::ostream& stream, const Quaternion& Value)
    {
        stream << "{" << Value.W << "," << Value.X << "," << Value.Y << "," << Value.Z << "}";
        return stream;
    }
};