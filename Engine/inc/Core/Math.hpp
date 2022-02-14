#pragma once

#include<cstdint>
#include<iostream>

namespace Hero
{

#define PI 3.141596f

template<typename T>
inline T min(T a, T b)
{
    return (a < b)? a : b;
}

template<typename T>
inline T max(T a, T b)
{
    return (a > b)? a : b;
}

struct Int2
{
    int x, y;

    constexpr static inline Int2 zero(){return (Int2){0, 0}; } 
    inline bool operator==(const Int2& other)
    {
        return x != other.x || y != other.y;
    }
};

#define Int2zero (Hero::Int2){0, 0}
#define Int2one (Hero::Int2){1, 1}

struct Int3
{
    int x, y, z;
};

#define Int3zero (Hero::Int3){0, 0, 0}
#define Int3one (Hero::Int3){1, 1, 1}

struct Int4
{
    int x, y, z, w;
};

#define Int4zero (Hero::Int4){0, 0, 0, 0}
#define Int4one (Hero::Int4){1, 1, 1, 1}

struct Float2
{
    float x, y;
};

#define Float2zero (Hero::Float2){0.0f, 0.0f}
#define Float2one (Hero::Float2){1.0f, 1.0f}

struct Float3
{
    float x, y, z;

    constexpr static inline Float3 zero(){return (Float3){0.0f, 0.0f, 0.0f}; } 
    constexpr static inline Float3 one(){return (Float3){1.0f, 1.0f, 1.0f}; } 
    constexpr static inline Float3 forward(){return (Float3){0.0f, 0.0f, 1.0f}; } 
    constexpr static inline Float3 up(){return (Float3){0.0f, 1.0f, 0.0f}; } 
    constexpr static inline Float3 right(){return (Float3){1.0f, 0.0f, 0.0f}; } 
};

struct Float4
{
    float x, y, z, w;

    constexpr static inline Float4 zero(){return (Float4){0.0f, 0.0f, 0.0f, 0.0f}; } 
    constexpr static inline Float4 one(){return (Float4){1.0f, 1.0f, 1.0f, 1.0f}; } 

    inline bool operator==(const Float4& other)
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }
};

struct Matrix2x2
{
    Float2 col[2];
};

#define matrix2x2identity (Hero::Matrix2x2){(Hero::Float2){1.0f,0.0f},(Hero::Float2){0.0f,1.0f}}

struct Matrix3x3
{
    Float3 col[3];
};

#define matrix3x3identity (Hero::Matrix3x3){(Hero::Float3){1.0f,0.0f,0.0f},(Hero::Float3){0.0f,1.0f,0.0f},(Hero::Float3){0.0f,0.0f,1.0f}}

struct Matrix4x4
{
    Float4 col[4];
    constexpr static inline Matrix4x4 identity(){
        return {(Float4){1.0f,0.0f,0.0f,0.0f},
                (Float4){0.0f,1.0f,0.0f,0.0f},
                (Float4){0.0f,0.0f,1.0f,0.0f},
                (Float4){0.0f,0.0f,0.0f,1.0f}};
    }
};

HERO float deg2rad(float degree);
HERO float rad2deg(float radians);
HERO int clampI(int value, int min, int max);
HERO float clampF(float value, float min, float max);

HERO Int2 addI2(Int2 A, Int2 B);
HERO Int2 substractI2(Int2 A, Int2 B);
HERO int dotProductI2(Int2 A, Int2 B);
HERO float distanceI2(Int2 A, Int2 B);
HERO std::ostream& operator<< (std::ostream& stream, const Int2& vector);

HERO Int3 addI3(Int3 A, Int3 B);
HERO Int3 substract(Int3 A, Int3 B);
HERO int dotProductI3(Int3 A, Int3 B);
HERO float distanceI3(Int3 A, Int3 B);

HERO Int4 addI4(Int4 A, Int4 B);
HERO Int4 substractI4(Int4 A, Int4 B);

HERO float lerpF(float a, float b, float t);

HERO Float2 addF2(Float2 A,Float2 B);
HERO Float2 substractF2(Float2 A,Float2 B);
HERO float dotProductF2(Float2 A,Float2 B);
HERO Float2 multiplyF2(Float2 A, float k);
HERO Float2 normalizeF2(Float2 A);
HERO float lengthF2(Float2 A);
HERO float distanceF2(Float2 A, Float2 B);
HERO Float2 rotateF2(Float2 vector, float angle);

HERO Float3 addF3(Float3 A, Float3 B);
HERO Float3 substractF3(Float3 A, Float3 B);
HERO float dotProductF3(Float3 A, Float3 B);
HERO Float3 crossProduct(Float3 A, Float3 B);
HERO Float3 multiplyF3(Float3 A, float k);
HERO Float3 multiplyF3F3(Float3 A, Float3 B);
HERO Float3 normalizeF3(Float3 A);
HERO float lengthF3(Float3 A);
HERO Float3 lerpF3(Float3 A, Float3 B, float t);
HERO float distanceF3(Float3 A, Float3 B);
HERO std::ostream& operator<< (std::ostream& stream, const Float3& vector);

HERO Float4 addF4(Float4 A, Float4 B);
HERO Float4 substractF4(Float4 A, Float4 B);
HERO Float4 multiplyF4(Float4 A, float k);
HERO Float4 normalizeF4(Float4 A);
HERO float lengthF4(Float4 A);
HERO std::ostream& operator<< (std::ostream& stream, const Float4& vector);

HERO Matrix2x2 multiplyM2x2(Matrix2x2 A, Matrix2x2 B);
HERO float determinentM2x2(Matrix2x2 A);
HERO Matrix2x2 tansponeM2x2(Matrix2x2 A);
HERO Matrix2x2 invertM2x2(Matrix2x2 A);
HERO Float2 multiplyM2x2F2(Matrix2x2 matrix, Float2 vector);

HERO Matrix3x3 multiplyM3x3(Matrix3x3 A, Matrix3x3 B);
HERO float determinentM3x3(Matrix3x3 A);
HERO Matrix3x3 tansponeM3x3(Matrix3x3 A);
HERO Matrix3x3 invertM3x3(Matrix3x3 A);
HERO Float3 multiplyM3x3F3(Matrix3x3 matrix, Float3 vector);

HERO Matrix4x4 multiplyM4x4(Matrix4x4 A, Matrix4x4 B);
HERO float determinentM4x4(Matrix4x4 A);
HERO Matrix4x4 tansponeM4x4(Matrix4x4 A);
HERO Matrix4x4 invertM4x4(Matrix4x4 A);
HERO Float4 multiplyM4x4F4(Matrix4x4 matrix, Float4 vector);
HERO float* m4x4ToArray(Matrix4x4 A);
HERO Matrix4x4 arrayToM4x4(float* array);

HERO void translateM4x4(Matrix4x4* matrix, Float3 translation);
HERO void scaleM4x4(Matrix4x4* matrix, Float3 scale);
HERO void rotateXM4x4(Matrix4x4* matrix, float radians);
HERO void rotateYM4x4(Matrix4x4* matrix, float radians);
HERO void rotateZM4x4(Matrix4x4* matrix, float radians);
HERO void rotateXYZM4x4(Matrix4x4* matrix, Float3 rotation);

HERO Matrix4x4 pixelScreenMatrix(int width, int height, float near, float far);
HERO Matrix4x4 projectionMatrix(int width, int height, float FOV, float near, float far);
HERO Matrix4x4 lookAtMatrix(Float3 eye, Float3 target, Float3 up);
HERO Matrix4x4 orthographicMatrix(int width, int height, float near, float far); // need to be rework

HERO bool pointBoxIntersection(Int2 point, Int2 boxPosition, Int2 boxSize);

}
