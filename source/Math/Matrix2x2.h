#pragma once

#include "../Definitions.h"
#include "../GenericTypes/String.h"
#include <iostream>
#include "Float2.h"

struct HERO_API Matrix2x2
{
    Float2 Column[2];

    constexpr Matrix2x2() {};
    constexpr Matrix2x2(const Float2& Vector1, const Float2& Vector2)
    {
        Column[0] = Vector1;
        Column[1] = Vector2;
    }

    constexpr static Matrix2x2 Identity() {
        return { Float2(1.0f,0.0f),
                Float2(0.0f,1.0f) };
    }

    Matrix2x2(const String& Str);

    float Determinant() const;
    Matrix2x2 Tansponed() const;
    Matrix2x2 Inverted() const;

    Matrix2x2& operator+=(const Matrix2x2& Other);
    Matrix2x2& operator-=(const Matrix2x2& Other);
    Matrix2x2& operator*=(const Matrix2x2& Other);
    Matrix2x2& operator*=(float Scalar);

    Matrix2x2 operator+(const Matrix2x2& Other) const;
    Matrix2x2 operator-(const Matrix2x2& Other) const;
    Matrix2x2 operator*(const Matrix2x2& Other) const;
    Float2 operator*(const Float2& Other) const;
    Matrix2x2 operator*(float Scalar) const;

    friend std::ostream& operator<< (std::ostream& Stream, const Matrix2x2& Value)
    {
        Stream << "{" << Value.Column[0] << "," << Value.Column[1] << "}";
        return Stream;
    }
};
