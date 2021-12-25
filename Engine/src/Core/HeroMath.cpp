#include"Core/HeroMath.hpp"

#include<cmath>

namespace Hero
{

float MathDeg2rad(float degree)
{
    return (degree * PI)/180.0f;
}

float MathRad2deg(float radians)
{
    return (180.0f * radians)/PI;
}

int MathClampI(int value, int min, int max)
{
    return (value < min)? min : (value > max)? max : value;
}

float MathClampF(float value, float min, float max)
{
    return (value < min)? min : (value > max)? max : value;
}

Int2 MathAddI2(Int2 A, Int2 B)
{
    return (Int2){A.x + B.x, A.y + B.y};
}

Int2 MathSubstractI2(Int2 A, Int2 B)
{
    return (Int2){A.x - B.x, A.y - B.y};
}

int MathDotProductI2(Int2 A, Int2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

float MathDistanceI2(Int2 A, Int2 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

Int3 MathAddI3(Int3 A, Int3 B)
{
    return (Int3){A.x + B.x, A.y + B.y, A.z + B.z};
}

Int3 MathSubstract(Int3 A, Int3 B)
{
    return (Int3){A.x - B.x, A.y - B.y, A.z - B.z};
}

int MathDotProductI3(Int3 A, Int3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

float MathDistanceI3(Int3 A, Int3 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

Int4 MathAddI4(Int4 A, Int4 B)
{
    return (Int4){A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

Int4 MathSubstractI4(Int4 A, Int4 B)
{
    return (Int4){A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

float MathLerpF(float a, float b, float t)
{
    return (1 - t)*a + t*b;
}

Float2 MathAddF2(Float2 A,Float2 B)
{
    return (Float2){A.x + B.x, A.y + B.y};
}

Float2 MathSubstractF2(Float2 A,Float2 B)
{
    return (Float2){A.x - B.x, A.y - B.y};
}

float MathDotProductF2(Float2 A,Float2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

Float2 MathMultiplyF2(Float2 A, float k)
{
    return (Float2){A.x * k, A.y * k};
}

float MathLengthF2(Float2 A)
{
    return sqrtf(A.x*A.x + A.y*A.y);
}

Float2 MathNormalizeF2(Float2 A)
{
    float length = MathLengthF2(A);
    float x = A.x / length;
    float y = A.y / length;
    return (Float2){x, y};
}

float MathDistanceF2(Float2 A, Float2 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

Float2 MathRotateM2x2F2(Float2 vector, float angle)
{
    float x = vector.x * cos(angle) - vector.y * sin(angle);
    float y = vector.x * sin(angle) + vector.y * cos(angle);
    return (Float2){x, y};
}

Float3 MathAddF3(Float3 A, Float3 B)
{
    return (Float3){A.x + B.x, A.y + B.y, A.z + B.z};
}

Float3 MathSubstractF3(Float3 A, Float3 B)
{
    return (Float3){A.x - B.x, A.y - B.y, A.z - B.z};
}

float MathDotProductF3(Float3 A, Float3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

Float3 MathCrossProduct(Float3 A, Float3 B)
{
    return (Float3){A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.y, A.x*B.y - A.y*B.x};
}

Float3 MathMultiplyF3(Float3 A, float k)
{
    return (Float3){A.x * k, A.y * k, A.z * k};
}

float MathLengthF3(Float3 A)
{
    return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z);
}

Float3 MathNormalizeF3(Float3 A)
{
    float length = MathLengthF3(A);
    float x = A.x / length;
    float y = A.y / length;
    float z = A.z / length;
    return (Float3){x, y, z};
}

Float3 MathLerpF3(Float3 A, Float3 B, float t)
{
    float x = (1 - t)*A.x + t*B.x;
    float y = (1 - t)*A.y + t*B.y;
    float z = (1 - t)*A.z + t*B.z;
    return (Float3){x, y, z};
}

float MathDistanceF3(Float3 A, Float3 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

Float4 MathAddF4(Float4 A, Float4 B)
{
    return (Float4){A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

Float4 MathSubstractF4(Float4 A, Float4 B)
{
    return (Float4){A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

Float4 MathMultiplyF4(Float4 A, float k)
{
    return (Float4){A.x * k, A.y * k, A.z * k, A.w * k};
}

float MathLengthF4(Float4 A)
{
    return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z + A.w*A.w);
}

Float4 MathNormalizeF4(Float4 A)
{
    float length = MathLengthF4(A);
    float x = A.x / length;
    float y = A.y / length;
    float z = A.z / length;
    float w = A.w / length;
    return (Float4){x, y, z, w};
}

Matrix2x2 MathMultiplyM2x2(Matrix2x2 A, Matrix2x2 B)
{
    float x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y;
    float y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y;
    float z = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y;
    float w = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y;
    return (Matrix2x2){(Float2){x,y},(Float2){z,w}};
}   

float MathDeterminentM2x2(Matrix2x2 A)
{
    return (A.col[0].x * A.col[1].y) - (A.col[0].y * A.col[1].x);
}

Matrix2x2 MathTansponeM2x2(Matrix2x2 A)
{
    return (Matrix2x2){(Float2){A.col[0].x, A.col[1].x},(Float2){A.col[0].y, A.col[1].y}};
}

Matrix2x2 MathInvertM2x2(Matrix2x2 A)
{
    float det = 1.0f / MathDeterminentM2x2(A);
    return (Matrix2x2){(Float2){det * A.col[1].y, det * (-A.col[0].y)},
            (Float2){det * (-A.col[1].x), det * A.col[0].x}};
}

Float2 MathMultiplyM2x2F2(Matrix2x2 matrix, Float2 vector)
{
    float x = matrix.col[0].x * vector.x + matrix.col[1].x * vector.y;
    float y = matrix.col[0].y * vector.x + matrix.col[1].y * vector.y;
    return (Float2){x, y};
}

Matrix3x3 MathMultiplyM3x3(Matrix3x3 A, Matrix3x3 B)
{
    Matrix3x3 matrix;

    matrix.col[0].x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y + A.col[2].x * B.col[0].z;
    matrix.col[0].y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y + A.col[2].y * B.col[0].z;
    matrix.col[0].z = A.col[0].z * B.col[0].x + A.col[1].z * B.col[0].y + A.col[2].z * B.col[0].z;

    matrix.col[1].x = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y + A.col[2].x * B.col[1].z;
    matrix.col[1].y = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y + A.col[2].y * B.col[1].z;
    matrix.col[1].z = A.col[0].z * B.col[1].x + A.col[1].z * B.col[1].y + A.col[2].z * B.col[1].z;

    matrix.col[2].x = A.col[0].x * B.col[2].x + A.col[1].x * B.col[2].y + A.col[2].x * B.col[2].z;
    matrix.col[2].y = A.col[0].y * B.col[2].x + A.col[1].y * B.col[2].y + A.col[2].y * B.col[2].z;
    matrix.col[2].z = A.col[0].z * B.col[2].x + A.col[1].z * B.col[2].y + A.col[2].z * B.col[2].z;

    return matrix;
}

float MathDeterminentM3x3(Matrix3x3 A)
{
    return A.col[0].x*A.col[1].y*A.col[2].z + 
            A.col[1].x*A.col[2].y*A.col[0].z + 
            A.col[2].x*A.col[0].y*A.col[1].z -
            A.col[2].x*A.col[1].y*A.col[0].z - 
            A.col[1].x*A.col[0].y*A.col[2].z - 
            A.col[0].x*A.col[2].y*A.col[1].z;
}

Matrix3x3 MathTansponeM3x3(Matrix3x3 A)
{
    Matrix3x3 matrix;

    matrix.col[0].x = A.col[0].x;
    matrix.col[1].x = A.col[0].y;
    matrix.col[2].x = A.col[0].z;
    matrix.col[0].y = A.col[1].x;
    matrix.col[1].y = A.col[1].y;
    matrix.col[2].y = A.col[1].z;
    matrix.col[0].z = A.col[2].x;
    matrix.col[1].z = A.col[2].y;
    matrix.col[2].z = A.col[2].z;

    return matrix;
}

Matrix3x3 MathInvertM3x3(Matrix3x3 A)
{
    float det = 1.0f / MathDeterminentM3x3(A);

    Matrix3x3 matrix;

    matrix.col[0].x = (A.col[1].y * A.col[2].z) - (A.col[2].y * A.col[1].z);
    matrix.col[0].x *= det;
    matrix.col[0].y = (A.col[0].y * A.col[2].z) - (A.col[2].y * A.col[0].z);
    matrix.col[0].y *= -det;
    matrix.col[0].z = (A.col[0].y * A.col[1].z) - (A.col[1].y * A.col[0].z);
    matrix.col[0].z *= det;

    matrix.col[1].x = (A.col[1].x * A.col[2].z) - (A.col[2].x * A.col[1].z);
    matrix.col[1].x *= -det;
    matrix.col[1].y = (A.col[0].x * A.col[2].z) - (A.col[2].x * A.col[0].z);
    matrix.col[1].y *= det;
    matrix.col[1].z = (A.col[0].x * A.col[1].z) - (A.col[1].x * A.col[0].z);
    matrix.col[1].z *= -det;

    matrix.col[2].x = (A.col[1].x * A.col[2].y) - (A.col[2].x * A.col[1].y);
    matrix.col[2].x *= det;
    matrix.col[2].y = (A.col[0].x * A.col[2].y) - (A.col[2].x * A.col[0].y);
    matrix.col[2].y *= -det;
    matrix.col[2].z = (A.col[0].x * A.col[1].y) - (A.col[1].x * A.col[0].y);
    matrix.col[2].z *= det;

    return matrix;
}

Float3 MathMultiplyM3x3F3(Matrix3x3 matrix, Float3 vector)
{
    Float3 vec;

    vec.x = matrix.col[0].x * vector.x + matrix.col[1].x * vector.y + matrix.col[2].x * vector.z;
    vec.y = matrix.col[0].y * vector.x + matrix.col[1].y * vector.y + matrix.col[2].y * vector.z;
    vec.z = matrix.col[0].z * vector.x + matrix.col[2].z * vector.y + matrix.col[2].z * vector.z;
    
    return vec;
}

Matrix4x4 MathMultiplyM4x4(Matrix4x4 A, Matrix4x4 B)
{
    Matrix4x4 matrix;

    matrix.col[0].x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y + A.col[2].x * B.col[0].z + A.col[3].x * B.col[0].w;
    matrix.col[0].y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y + A.col[2].y * B.col[0].z + A.col[3].x * B.col[0].w;
    matrix.col[0].z = A.col[0].z * B.col[0].x + A.col[1].z * B.col[0].y + A.col[2].z * B.col[0].z + A.col[3].x * B.col[0].w;
    matrix.col[0].w = A.col[0].w * B.col[0].x + A.col[1].w * B.col[0].y + A.col[2].w * B.col[0].z + A.col[3].x * B.col[0].w;

    matrix.col[1].x = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y + A.col[2].x * B.col[1].z + A.col[3].x * B.col[1].w;
    matrix.col[1].y = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y + A.col[2].y * B.col[1].z + A.col[3].x * B.col[1].w;
    matrix.col[1].z = A.col[0].z * B.col[1].x + A.col[1].z * B.col[1].y + A.col[2].z * B.col[1].z + A.col[3].x * B.col[1].w;
    matrix.col[1].z = A.col[0].w * B.col[1].x + A.col[1].w * B.col[1].y + A.col[2].w * B.col[1].z + A.col[3].x * B.col[1].w;

    matrix.col[2].x = A.col[0].x * B.col[2].x + A.col[1].x * B.col[2].y + A.col[2].x * B.col[2].z + A.col[3].x * B.col[2].w;
    matrix.col[2].y = A.col[0].y * B.col[2].x + A.col[1].y * B.col[2].y + A.col[2].y * B.col[2].z + A.col[3].x * B.col[2].w;
    matrix.col[2].z = A.col[0].z * B.col[2].x + A.col[1].z * B.col[2].y + A.col[2].z * B.col[2].z + A.col[3].x * B.col[2].w;
    matrix.col[2].w = A.col[0].w * B.col[2].w + A.col[1].w * B.col[2].y + A.col[2].w * B.col[2].z + A.col[3].x * B.col[2].w;

    matrix.col[3].x = A.col[0].x * B.col[2].x + A.col[1].x * B.col[2].y + A.col[2].x * B.col[2].z + A.col[3].x * B.col[3].w;
    matrix.col[3].y = A.col[0].y * B.col[2].x + A.col[1].y * B.col[2].y + A.col[2].y * B.col[2].z + A.col[3].x * B.col[3].w;
    matrix.col[3].z = A.col[0].z * B.col[2].x + A.col[1].z * B.col[2].y + A.col[2].z * B.col[2].z + A.col[3].x * B.col[3].w;
    matrix.col[3].w = A.col[0].w * B.col[2].x + A.col[1].w * B.col[2].y + A.col[2].w * B.col[2].z + A.col[3].x * B.col[3].w;

    return matrix;
}

float MathDeterminentM4x4(Matrix4x4 A)
{
    Matrix4x4 matrix = Mat4x4Identity;

    float mul = A.col[0].y / A.col[0].x;
    matrix.col[1].y = A.col[1].y - mul * A.col[1].x;
    matrix.col[2].y = A.col[2].y - mul * A.col[2].x;
    matrix.col[3].y = A.col[3].y - mul * A.col[3].x;

    mul = A.col[0].z / A.col[0].y;
    matrix.col[2].z = A.col[2].z - mul * A.col[2].y;
    matrix.col[3].z = A.col[3].z - mul * A.col[3].y;

    mul = A.col[0].w / A.col[0].z;
    matrix.col[2].w = A.col[2].w - mul * A.col[2].z;

    return matrix.col[0].x * matrix.col[1].y * matrix.col[2].z *matrix.col[3].w;
}

Matrix4x4 MathInvertM4x4(Matrix4x4 A)
{
    float* m = MathM4x4ToArray(A);
    float inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    free(m);

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        inv[i] *= det;

    return MathArrayToM4x4(inv); 
}

Matrix4x4 MathTansponeM4x4(Matrix4x4 A)
{
    Matrix4x4 matrix;

    matrix.col[0].x = A.col[0].x;
    matrix.col[1].x = A.col[0].y;
    matrix.col[2].x = A.col[0].z;
    matrix.col[3].x = A.col[0].w;

    matrix.col[0].y = A.col[1].x;
    matrix.col[1].y = A.col[1].y;
    matrix.col[2].y = A.col[1].z;
    matrix.col[3].y = A.col[1].w;

    matrix.col[0].z = A.col[2].x;
    matrix.col[1].z = A.col[2].y;
    matrix.col[2].z = A.col[2].z;
    matrix.col[3].z = A.col[2].w;

    matrix.col[0].w = A.col[3].x;
    matrix.col[1].w = A.col[3].y;
    matrix.col[2].w = A.col[3].z;
    matrix.col[3].w = A.col[3].w;

    return matrix;
}

Float4 MathMultiplyM4x4F4(Matrix4x4 matrix, Float4 vector)
{
    float x = vector.x*matrix.col[0].x + vector.y*matrix.col[1].x + vector.z*matrix.col[2].x + vector.w*matrix.col[3].x;
    float y = vector.x*matrix.col[0].y + vector.y*matrix.col[1].y + vector.z*matrix.col[2].y + vector.w*matrix.col[3].y;
    float z = vector.x*matrix.col[0].z + vector.y*matrix.col[1].z + vector.z*matrix.col[2].z + vector.w*matrix.col[3].z;
    float w = vector.x*matrix.col[0].w + vector.y*matrix.col[1].w + vector.z*matrix.col[2].w + vector.w*matrix.col[3].w;

    return (Float4){x, y, z, w};
}

float* MathM4x4ToArray(Matrix4x4 A)
{
    float* arr = (float*)malloc(16 * sizeof(float));

    arr[0] = A.col[0].x;
    arr[1] = A.col[0].y;
    arr[2] = A.col[0].z;
    arr[3] = A.col[0].w;

    arr[4] = A.col[1].x;
    arr[5] = A.col[1].y;
    arr[6] = A.col[1].z;
    arr[7] = A.col[1].w;

    arr[8] = A.col[2].x;
    arr[9] = A.col[2].y;
    arr[10] = A.col[2].z;
    arr[11] = A.col[2].w;

    arr[12] = A.col[3].x;
    arr[13] = A.col[3].y;
    arr[14] = A.col[3].z;
    arr[15] = A.col[3].w;

    return arr;
}

Matrix4x4 MathArrayToM4x4(float* array)
{
    Matrix4x4 result;

    result.col[0] = (Float4){array[0], array[4], array[8], array[12]};
    result.col[1] = (Float4){array[1], array[5], array[9], array[13]};
    result.col[2] = (Float4){array[2], array[6], array[10], array[14]};
    result.col[3] = (Float4){array[3], array[7], array[11], array[15]};

    return result;
}

void MathTranslateM4x4(Matrix4x4* matrix, Float4 translation)
{
    matrix->col[3].x += translation.x;
    matrix->col[3].y += translation.y;
    matrix->col[3].z += translation.z;
}

void MathScaleM4x4(Matrix4x4* matrix, Float4 scale)
{
    matrix->col[0].x = scale.x;
    matrix->col[1].y = scale.y;
    matrix->col[2].z = scale.z;
}

void MathRotateXM4x4(Matrix4x4* matrix, float radians)
{
    float a = matrix->col[0].y;
    float b = matrix->col[0].z;
    matrix->col[0].y = a*cosf(radians) - b*sinf(radians);
    matrix->col[0].z = a*sinf(radians) + b*cosf(radians);
    a = matrix->col[1].y;
    b = matrix->col[1].z;
    matrix->col[1].y = a*cosf(radians) - b*sinf(radians);
    matrix->col[1].z = a*sinf(radians) + b*cosf(radians);
    a = matrix->col[2].y;
    b = matrix->col[2].z;
    matrix->col[2].y = a*cosf(radians) - b*sinf(radians);
    matrix->col[2].z = a*sinf(radians) + b*cosf(radians);
    a = matrix->col[3].y;
    b = matrix->col[3].z;   
    matrix->col[3].y = a*cosf(radians) - b*sinf(radians);
    matrix->col[3].z = a*sinf(radians) + b*cosf(radians);
}

void MathRotateYM4x4(Matrix4x4* matrix, float radians)
{
    float a = matrix->col[0].x;
    float b = matrix->col[0].z;
    matrix->col[0].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[0].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix->col[1].x;
    b = matrix->col[1].z;
    matrix->col[1].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[1].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix->col[2].x;
    b = matrix->col[2].z;
    matrix->col[2].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[2].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix->col[3].x;
    b = matrix->col[3].z;   
    matrix->col[3].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[3].z = -a*sinf(radians) + b*cosf(radians);
}

void MathRotateZM4x4(Matrix4x4* matrix, float radians)
{
    float a = matrix->col[0].x;
    float b = matrix->col[0].y;
    matrix->col[0].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[0].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix->col[1].x;
    b = matrix->col[1].y;
    matrix->col[1].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[1].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix->col[2].x;
    b = matrix->col[2].y;
    matrix->col[2].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[2].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix->col[3].x;
    b = matrix->col[3].y;   
    matrix->col[3].x = a*cosf(radians) + b*sinf(radians);
    matrix->col[3].y = -a*sinf(radians) + b*cosf(radians);
}

void MathRotateXYZM4x4(Matrix4x4* matrix, Float4 rotation)
{
    if(rotation.x != 0.0f)
        MathRotateXM4x4(matrix, rotation.x);
    if(rotation.y != 0.0f)
        MathRotateYM4x4(matrix, rotation.y);
    if(rotation.z != 0.0f)
        MathRotateZM4x4(matrix, rotation.z);
}

Matrix4x4 MathPixelScreenMatrix(int width, int height, float near, float far)
{
    Matrix4x4 matrix = Mat4x4Identity;
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = -2.0f/(far - near);
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = (far + near)/(far - near);
    matrix.col[3].w = 1;
    return matrix;
}

Matrix4x4 MathProjectionMatrix(int width, int height, float FOV, float near, float far)
{
    float aspectRatio = (float)width/(float)height;
    float tg = tanf(FOV*0.5f*PI/180.0f);

    Matrix4x4 matrix = Mat4x4Identity;

    matrix.col[0].x = 1.0f/(aspectRatio*tg);
    matrix.col[1].y = 1.0f/tg;
    matrix.col[2].z = -far/(near - far);
    matrix.col[3].z = (far*near)/(near - far);

    return matrix;
}

Matrix4x4 MathLookAtMatrix(Float3 eye, Float3 target, Float3 up)
{
    Float3 f = MathSubstractF3(target, eye);
    f = MathNormalizeF3(f);

    Float3 r = MathCrossProduct(f, up);
    r = (Float3){-r.x, -r.y, -r.z};
    r = MathNormalizeF3(r);

    Float3 u = MathCrossProduct(r, f);
    u = (Float3){-u.x, -u.y, -u.z};

    Matrix4x4 matrix;

    matrix.col[0].x = r.x;
    matrix.col[1].x = r.y;
    matrix.col[2].x = r.z;

    matrix.col[0].y = u.x;
    matrix.col[1].y = u.y;
    matrix.col[2].y = u.z;

    matrix.col[0].z = f.x;
    matrix.col[1].z = f.y;
    matrix.col[2].z = f.z;

    matrix.col[0].w = 0.0f;
    matrix.col[1].w = 0.0f;
    matrix.col[2].w = 0.0f;

    matrix.col[3].x = -MathDotProductF3(r,eye);
    matrix.col[3].y = -MathDotProductF3(u,eye);
    matrix.col[3].z = -MathDotProductF3(f,eye);
    matrix.col[3].w = 1.0f;

    return matrix;
}

Matrix4x4 MathOrthographicMatrix(int width, int height, float near, float far)
{
    Matrix4x4 matrix = Mat4x4Identity;
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = -2.0f/(far - near);
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = (far + near)/(far - near);
    matrix.col[3].w = 1;
    return matrix;
}

}