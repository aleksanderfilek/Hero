#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"
#include <iostream>
#include "Float3.h"

struct HERO_API Matrix3x3
{
    Float3 Column[3];

    Matrix3x3() {}
    constexpr Matrix3x3(const Float3& Vector1, const Float3& Vector2, 
        const Float3& Vector3) {
        Column[0] = Vector1;
        Column[1] = Vector2;
        Column[2] = Vector3;
    }
    //Matrix3x3(const Matrix4x4& matrix);

    constexpr static Matrix3x3 Identity() {
        return Matrix3x3(Float3(1.0f, 0.0f, 0.0f),
            Float3(0.0f, 1.0f, 0.0f),
            Float3(0.0f, 0.0f, 1.0f));
    }

    float Determinant() const;
    Matrix3x3 Tansponed() const;
    Matrix3x3 Inverted() const;

    Matrix3x3& operator+=(const Matrix3x3& Other);
    Matrix3x3& operator-=(const Matrix3x3& Other);
    Matrix3x3& operator*=(const Matrix3x3& Other);
    Matrix3x3& operator*=(float Scalar);

    Matrix3x3 operator+(const Matrix3x3& Other) const;
    Matrix3x3 operator-(const Matrix3x3& Other) const;
    Matrix3x3 operator*(const Matrix3x3& Other) const;
    Float3 operator*(const Float3& Other) const;
    Matrix3x3 operator*(float Scalar) const;

    friend std::ostream& operator<< (std::ostream& Stream, const Matrix3x3& Value)
    {
        Stream << "{" << Value.Column[0] << "," << Value.Column[1] 
            << "," << Value.Column[2] << "}";
        return Stream;
    }
};