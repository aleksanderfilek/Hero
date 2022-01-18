#pragma once

#include<cstdint>

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

typedef struct
{
    int x, y;
} Int2;

#define Int2zero (Int2){0, 0}
#define Int2one (Int2){1, 1}

typedef struct
{
    int x, y, z;
} Int3;

#define Int3zero (Int3){0, 0, 0}
#define Int3one (Int3){1, 1, 1}

typedef struct
{
    int x, y, z, w;
} Int4;

#define Int4zero (Int4){0, 0, 0, 0}
#define Int4one (Int4){1, 1, 1, 1}

typedef struct
{
    float x, y;
} Float2;

#define Float2zero (Float2){0.0f, 0.0f}
#define Float2one (Float2){1.0f, 1.0f}

typedef struct
{
    float x, y, z;
} Float3;

#define Float3zero (Float3){0.0f, 0.0f, 0.0f}
#define Float3one (Float3){1.0f, 1.0f, 1.0f}

typedef struct
{
    float x, y, z, w;
} Float4;

#define Float4zero (Float4){0.0f, 0.0f, 0.0f, 0.0f}
#define Float4one (Float4){1.0f, 1.0f, 1.0f, 1.0f}

typedef struct
{
    Float2 col[2];
} Matrix2x2;

#define matrix2x2identity (Matrix2x2){(Float2){1.0f,0.0f},(Float2){0.0f,1.0f}}

typedef struct
{
    Float3 col[3];
} Matrix3x3;

#define matrix3x3identity (Matrix3x3){(Float3){1.0f,0.0f,0.0f},(Float3){0.0f,1.0f,0.0f},(Float3){0.0f,0.0f,1.0f}}

typedef struct
{
    Float4 col[4];
} Matrix4x4;

#define Mat4x4Identity (Matrix4x4){(Float4){1.0f,0.0f,0.0f,0.0f},(Float4){0.0f,1.0f,0.0f,0.0f},(Float4){0.0f,0.0f,1.0f,0.0f},(Float4){0.0f,0.0f,0.0f,1.0f}}

float deg2rad(float degree);
float rad2deg(float radians);
int clampI(int value, int min, int max);
float clampF(float value, float min, float max);

Int2 addI2(Int2 A, Int2 B);
Int2 substractI2(Int2 A, Int2 B);
int dotProductI2(Int2 A, Int2 B);
float distanceI2(Int2 A, Int2 B);

Int3 addI3(Int3 A, Int3 B);
Int3 substract(Int3 A, Int3 B);
int dotProductI3(Int3 A, Int3 B);
float distanceI3(Int3 A, Int3 B);

Int4 addI4(Int4 A, Int4 B);
Int4 substractI4(Int4 A, Int4 B);

float lerpF(float a, float b, float t);

Float2 addF2(Float2 A,Float2 B);
Float2 substractF2(Float2 A,Float2 B);
float dotProductF2(Float2 A,Float2 B);
Float2 multiplyF2(Float2 A, float k);
Float2 normalizeF2(Float2 A);
float lengthF2(Float2 A);
float distanceF2(Float2 A, Float2 B);
Float2 rotateF2(Float2 vector, float angle);

Float3 addF3(Float3 A, Float3 B);
Float3 substractF3(Float3 A, Float3 B);
float dotProductF3(Float3 A, Float3 B);
Float3 drossProduct(Float3 A, Float3 B);
Float3 multiplyF3(Float3 A, float k);
Float3 normalizeF3(Float3 A);
float lengthF3(Float3 A);
Float3 lerpF3(Float3 A, Float3 B, float t);
float distanceF3(Float3 A, Float3 B);

Float4 addF4(Float4 A, Float4 B);
Float4 substractF4(Float4 A, Float4 B);
Float4 multiplyF4(Float4 A, float k);
Float4 normalizeF4(Float4 A);
float lengthF4(Float4 A);

Matrix2x2 multiplyM2x2(Matrix2x2 A, Matrix2x2 B);
float determinentM2x2(Matrix2x2 A);
Matrix2x2 tansponeM2x2(Matrix2x2 A);
Matrix2x2 invertM2x2(Matrix2x2 A);
Float2 multiplyM2x2F2(Matrix2x2 matrix, Float2 vector);

Matrix3x3 multiplyM3x3(Matrix3x3 A, Matrix3x3 B);
float determinentM3x3(Matrix3x3 A);
Matrix3x3 tansponeM3x3(Matrix3x3 A);
Matrix3x3 invertM3x3(Matrix3x3 A);
Float3 multiplyM3x3F3(Matrix3x3 matrix, Float3 vector);

Matrix4x4 multiplyM4x4(Matrix4x4 A, Matrix4x4 B);
float determinentM4x4(Matrix4x4 A);
Matrix4x4 tansponeM4x4(Matrix4x4 A);
Matrix4x4 invertM4x4(Matrix4x4 A);
Float4 multiplyM4x4F4(Matrix4x4 matrix, Float4 vector);
float* m4x4ToArray(Matrix4x4 A);
Matrix4x4 arrayToM4x4(float* array);

void translateM4x4(Matrix4x4* matrix, Float4 translation);
void scaleM4x4(Matrix4x4* matrix, Float4 scale);
void rotateXM4x4(Matrix4x4* matrix, float radians);
void rotateYM4x4(Matrix4x4* matrix, float radians);
void rotateZM4x4(Matrix4x4* matrix, float radians);
void rotateXYZM4x4(Matrix4x4* matrix, Float4 rotation);

Matrix4x4 pixelScreenMatrix(int width, int height, float near, float far);
Matrix4x4 projectionMatrix(int width, int height, float FOV, float near, float far);
Matrix4x4 lookAtMatrix(Float3 eye, Float3 target, Float3 up);
Matrix4x4 orthographicMatrix(int width, int height, float near, float far); // need to be rework

}
