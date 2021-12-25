#pragma once

namespace Hero
{
#define PI 3.141596f

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

float MathDeg2rad(float degree);
float MathRad2deg(float radians);
int MathClampI(int value, int min, int max);
float MathClampF(float value, float min, float max);

Int2 MathAddI2(Int2 A, Int2 B);
Int2 MathSubstractI2(Int2 A, Int2 B);
int MathDotProductI2(Int2 A, Int2 B);
float MathDistanceI2(Int2 A, Int2 B);

Int3 MathAddI3(Int3 A, Int3 B);
Int3 MathSubstract(Int3 A, Int3 B);
int MathDotProductI3(Int3 A, Int3 B);
float MathDistanceI3(Int3 A, Int3 B);

Int4 MathAddI4(Int4 A, Int4 B);
Int4 MathSubstractI4(Int4 A, Int4 B);

float MathLerpF(float a, float b, float t);

Float2 MathAddF2(Float2 A,Float2 B);
Float2 MathSubstractF2(Float2 A,Float2 B);
float MathDotProductF2(Float2 A,Float2 B);
Float2 MathMultiplyF2(Float2 A, float k);
Float2 MathNormalizeF2(Float2 A);
float MathLengthF2(Float2 A);
float MathDistanceF2(Float2 A, Float2 B);
Float2 MathRotateF2(Float2 vector, float angle);

Float3 MathAddF3(Float3 A, Float3 B);
Float3 MathSubstractF3(Float3 A, Float3 B);
float MathDotProductF3(Float3 A, Float3 B);
Float3 MathCrossProduct(Float3 A, Float3 B);
Float3 MathMultiplyF3(Float3 A, float k);
Float3 MathNormalizeF3(Float3 A);
float MathLengthF3(Float3 A);
Float3 MathLerpF3(Float3 A, Float3 B, float t);
float MathDistanceF3(Float3 A, Float3 B);

Float4 MathAddF4(Float4 A, Float4 B);
Float4 MathSubstractF4(Float4 A, Float4 B);
Float4 MathMultiplyF4(Float4 A, float k);
Float4 MathNormalizeF4(Float4 A);
float MathLengthF4(Float4 A);

Matrix2x2 MathMultiplyM2x2(Matrix2x2 A, Matrix2x2 B);
float MathDeterminentM2x2(Matrix2x2 A);
Matrix2x2 MathTansponeM2x2(Matrix2x2 A);
Matrix2x2 MathInvertM2x2(Matrix2x2 A);
Float2 MathMultiplyM2x2F2(Matrix2x2 matrix, Float2 vector);

Matrix3x3 MathMultiplyM3x3(Matrix3x3 A, Matrix3x3 B);
float MathDeterminentM3x3(Matrix3x3 A);
Matrix3x3 MathTansponeM3x3(Matrix3x3 A);
Matrix3x3 MathInvertM3x3(Matrix3x3 A);
Float3 MathMultiplyM3x3F3(Matrix3x3 matrix, Float3 vector);

Matrix4x4 MathMultiplyM4x4(Matrix4x4 A, Matrix4x4 B);
float MathDeterminentM4x4(Matrix4x4 A);
Matrix4x4 MathTansponeM4x4(Matrix4x4 A);
Matrix4x4 MathInvertM4x4(Matrix4x4 A);
Float4 MathMultiplyM4x4F4(Matrix4x4 matrix, Float4 vector);
float* MathM4x4ToArray(Matrix4x4 A);
Matrix4x4 MathArrayToM4x4(float* array);

void MathTranslateM4x4(Matrix4x4* matrix, Float4 translation);
void MathScaleM4x4(Matrix4x4* matrix, Float4 scale);
void MathRotateXM4x4(Matrix4x4* matrix, float radians);
void MathRotateYM4x4(Matrix4x4* matrix, float radians);
void MathRotateZM4x4(Matrix4x4* matrix, float radians);
void MathRotateXYZM4x4(Matrix4x4* matrix, Float4 rotation);

Matrix4x4 MathPixelScreenMatrix(int width, int height, float near, float far);

Matrix4x4 MathProjectionMatrix(int width, int height, float FOV, float near, float far);
Matrix4x4 MathLookAtMatrix(Float3 eye, Float3 target, Float3 up);
Matrix4x4 MathOrthographicMatrix(int width, int height, float near, float far);

}
