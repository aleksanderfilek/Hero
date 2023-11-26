#pragma once

#include "../Definitions.h"
#include <iostream>
#include "Float4.h"
#include "Float3.h"
#include "Quaternion.h"
#include "Int2.h"

struct HERO_API Matrix4x4
{
    Float4 Column[4];

    Matrix4x4() {}
    constexpr Matrix4x4(const Float4& Vector1, const Float4& Vector2, 
        const Float4& Vector3, const Float4& Vector4) {
        Column[0] = Vector1;
        Column[1] = Vector2;
        Column[2] = Vector3;
        Column[3] = Vector4;
    }
    //Matrix4x4(const Matrix3x3& matrix);

    constexpr static Matrix4x4 Identity() {
        return { Float4(1.0f,0.0f,0.0f,0.0f),
                Float4(0.0f,1.0f,0.0f,0.0f),
                Float4(0.0f,0.0f,1.0f,0.0f),
                Float4(0.0f,0.0f,0.0f,1.0f) };
    }

    float Determinent() const;
    Matrix4x4 Tansponed() const;
    Matrix4x4 Inverted() const;

    Matrix4x4& operator+=(const Matrix4x4& Other);
    Matrix4x4& operator-=(const Matrix4x4& Other);
    Matrix4x4& operator*=(const Matrix4x4& Other);
    Matrix4x4& operator*=(float Scalar);

    Matrix4x4 operator+(const Matrix4x4& Other) const;
    Matrix4x4 operator-(const Matrix4x4& Other) const;
    Matrix4x4 operator*(const Matrix4x4& Other) const;
    Float4 operator*(const Float4& Other) const;
    Matrix4x4 operator*(float Scalar) const;

    friend std::ostream& operator<< (std::ostream& Stream, const Matrix4x4& Value)
    {
        Stream << "{" << Value.Column[0] << "," << Value.Column[1] 
            << "," << Value.Column[2] << "," << Value.Column[3] << "}";
        return Stream;
    }

    static void Translate(Matrix4x4& Matrix, const Float3& Translation);
    static void Scale(Matrix4x4& Matrix, const Float3& Dcale);
    static void RotateX(Matrix4x4& Matrix, float Radians);
    static void RotateY(Matrix4x4& Matrix, float Radians);
    static void RotateZ(Matrix4x4& Matrix, float Radians);
    static void RotateXYZ(Matrix4x4& Matrix, const Float3& Rotation);
    static Matrix4x4 Rotation(const Quaternion& Rotation);

    static Matrix4x4 TRS(const Float3& Position, const Float3& Rotation, const Float3& Scale);
    static Matrix4x4 TRS(const Float3& Position, const Quaternion& Rotation, const Float3& Scale);

    static Matrix4x4 PixelScreenMatrix(const Int2& Size, float Near, float Far);
    static Matrix4x4 ProjectionMatrix(const Int2& Size, float FOV, float Near, float Far);
    static Matrix4x4 LookAtMatrix(const Float3& Eye, const Float3& Target, const Float3& UpVector);
    static Matrix4x4 OrthographicMatrix(const Int2& Size, float Near, float Far);
};