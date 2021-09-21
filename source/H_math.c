#include"H_math.h"
#include<math.h>
#include<stdlib.h>

#define PI 3.141596f

float heroMathDeg2rad(float degree)
{
    return (degree * PI)/180.0f;
}

float heroMathRad2deg(float radians)
{
    return (180.0f * radians)/PI;
}

int heroMathClampI(int value, int min, int max)
{
    return (value < min)? min : (value > max)? max : value;
}

float heroMathClampF(float value, float min, float max)
{
    return (value < min)? min : (value > max)? max : value;
}

HeroInt2 heroMathAddI2(HeroInt2 A, HeroInt2 B)
{
    return (HeroInt2){A.x + B.x, A.y + B.y};
}

HeroInt2 heroMathSubstractI2(HeroInt2 A, HeroInt2 B)
{
    return (HeroInt2){A.x - B.x, A.y - B.y};
}

int heroMathDotProductI2(HeroInt2 A, HeroInt2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

float heroMathDistanceI2(HeroInt2 A, HeroInt2 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

HeroInt3 heroMathAddI3(HeroInt3 A, HeroInt3 B)
{
    return (HeroInt3){A.x + B.x, A.y + B.y, A.z + B.z};
}

HeroInt3 heroMathSubstract(HeroInt3 A, HeroInt3 B)
{
    return (HeroInt3){A.x - B.x, A.y - B.y, A.z - B.z};
}

int heroMathDotProductI3(HeroInt3 A, HeroInt3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

float heroMathDistanceI3(HeroInt3 A, HeroInt3 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

HeroInt4 heroMathAddI4(HeroInt4 A, HeroInt4 B)
{
    return (HeroInt4){A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

HeroInt4 heroMathSubstractI4(HeroInt4 A, HeroInt4 B)
{
    return (HeroInt4){A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

float heroMathLerpF(float a, float b, float t)
{
    return (1 - t)*a + t*b;
}

HeroFloat2 heroMathAddF2(HeroFloat2 A,HeroFloat2 B)
{
    return (HeroFloat2){A.x + B.x, A.y + B.y};
}

HeroFloat2 heroMathSubstractF2(HeroFloat2 A,HeroFloat2 B)
{
    return (HeroFloat2){A.x - B.x, A.y - B.y};
}

float heroMathDotProductF2(HeroFloat2 A,HeroFloat2 B)
{
    return (A.x * B.x) + (A.y * B.y);
}

HeroFloat2 heroMathMultiplyF2(HeroFloat2 A, float k)
{
    return (HeroFloat2){A.x * k, A.y * k};
}

float heroMathLengthF2(HeroFloat2 A)
{
    return sqrtf(A.x*A.x + A.y*A.y);
}

HeroFloat2 heroMathNormalizeF2(HeroFloat2 A)
{
    float length = heroMathLengthF2(A);
    float x = A.x / length;
    float y = A.y / length;
    return (HeroFloat2){x, y};
}

float heroMathDistanceF2(HeroFloat2 A, HeroFloat2 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

HeroFloat3 heroMathAddF3(HeroFloat3 A, HeroFloat3 B)
{
    return (HeroFloat3){A.x + B.x, A.y + B.y, A.z + B.z};
}

HeroFloat3 heroMathSubstractF3(HeroFloat3 A, HeroFloat3 B)
{
    return (HeroFloat3){A.x - B.x, A.y - B.y, A.z - B.z};
}

float heroMathDotProductF3(HeroFloat3 A, HeroFloat3 B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

HeroFloat3 heroMathCrossProduct(HeroFloat3 A, HeroFloat3 B)
{
    return (HeroFloat3){A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.y, A.x*B.y - A.y*B.x};
}

HeroFloat3 heroMathMultiplyF3(HeroFloat3 A, float k)
{
    return (HeroFloat3){A.x * k, A.y * k, A.z * k};
}

float heroMathLengthF3(HeroFloat3 A)
{
    return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z);
}

HeroFloat3 heroMathNormalizeF3(HeroFloat3 A)
{
    float length = heroMathLengthF3(A);
    float x = A.x / length;
    float y = A.y / length;
    float z = A.z / length;
    return (HeroFloat3){x, y, z};
}

HeroFloat3 heroMathLerpF3(HeroFloat3 A, HeroFloat3 B, float t)
{
    float x = (1 - t)*A.x + t*B.x;
    float y = (1 - t)*A.y + t*B.y;
    float z = (1 - t)*A.z + t*B.z;
    return (HeroFloat3){x, y, z};
}

float heroMathDistanceF3(HeroFloat3 A, HeroFloat3 B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

HeroFloat4 heroMathAddF4(HeroFloat4 A, HeroFloat4 B)
{
    return (HeroFloat4){A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

HeroFloat4 heroMathSubstractF4(HeroFloat4 A, HeroFloat4 B)
{
    return (HeroFloat4){A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

HeroFloat4 heroMathMultiplyF4(HeroFloat4 A, float k)
{
    return (HeroFloat4){A.x * k, A.y * k, A.z * k, A.w * k};
}

float heroMathLengthF4(HeroFloat4 A)
{
    return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z + A.w*A.w);
}

HeroFloat4 heroMathNormalizeF4(HeroFloat4 A)
{
    float length = heroMathLengthF4(A);
    float x = A.x / length;
    float y = A.y / length;
    float z = A.z / length;
    float w = A.w / length;
    return (HeroFloat4){x, y, z, w};
}

HeroMatrix2x2 heroMathMultiplyM2x2(HeroMatrix2x2 A, HeroMatrix2x2 B)
{
    float x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y;
    float y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y;
    float z = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y;
    float w = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y;
    return (HeroMatrix2x2){(HeroFloat2){x,y},(HeroFloat2){z,w}};
}   

float heroMathDeterminentM2x2(HeroMatrix2x2 A)
{
    return (A.col[0].x * A.col[1].y) - (A.col[0].y * A.col[1].x);
}

HeroMatrix2x2 heroMathTansponeM2x2(HeroMatrix2x2 A)
{
    return (HeroMatrix2x2){(HeroFloat2){A.col[0].x, A.col[1].x},(HeroFloat2){A.col[0].y, A.col[1].y}};
}

HeroMatrix2x2 heroMathInvertM2x2(HeroMatrix2x2 A)
{
    float det = 1.0f / heroMathDeterminentM2x2(A);
    return (HeroMatrix2x2){(HeroFloat2){det * A.col[1].y, det * (-A.col[0].y)},
            (HeroFloat2){det * (-A.col[1].x), det * A.col[0].x}};
}

HeroFloat2 heroMathMultiplyM2x2F2(HeroMatrix2x2 matrix, HeroFloat2 vector)
{
    float x = matrix.col[0].x * vector.x + matrix.col[1].x * vector.y;
    float y = matrix.col[0].y * vector.x + matrix.col[1].y * vector.y;
    return (HeroFloat2){x, y};
}

HeroMatrix3x3 heroMathMultiplyM3x3(HeroMatrix3x3 A, HeroMatrix3x3 B)
{
    HeroMatrix3x3 matrix;

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

float heroMathDeterminentM3x3(HeroMatrix3x3 A)
{
    return A.col[0].x*A.col[1].y*A.col[2].z + 
            A.col[1].x*A.col[2].y*A.col[0].z + 
            A.col[2].x*A.col[0].y*A.col[1].z -
            A.col[2].x*A.col[1].y*A.col[0].z - 
            A.col[1].x*A.col[0].y*A.col[2].z - 
            A.col[0].x*A.col[2].y*A.col[1].z;
}

HeroMatrix3x3 heroMathTansponeM3x3(HeroMatrix3x3 A)
{
    HeroMatrix3x3 matrix;

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

HeroMatrix3x3 heroMathInvertM3x3(HeroMatrix3x3 A)
{
    float det = 1.0f / heroMathDeterminentM3x3(A);

    HeroMatrix3x3 matrix;

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

HeroFloat3 heroMathMultiplyM3x3F3(HeroMatrix3x3 matrix, HeroFloat3 vector)
{
    HeroFloat3 vec;

    vec.x = matrix.col[0].x * vector.x + matrix.col[1].x * vector.y + matrix.col[2].x * vector.z;
    vec.y = matrix.col[0].y * vector.x + matrix.col[1].y * vector.y + matrix.col[2].y * vector.z;
    vec.z = matrix.col[0].z * vector.x + matrix.col[2].z * vector.y + matrix.col[2].z * vector.z;
    
    return vec;
}

HeroMatrix4x4 heroMathMultiplyM4x4(HeroMatrix4x4 A, HeroMatrix4x4 B)
{
    HeroMatrix4x4 matrix;

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

float heroMathDeterminentM4x4(HeroMatrix4x4 A)
{
    HeroMatrix4x4 matrix = heroMat4x4Identity;

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

HeroMatrix4x4 heroMathInvertM4x4(HeroMatrix4x4 A)
{
    float* m = heroMathM4x4ToArray(A);
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

    return heroMathArrayToM4x4(inv); 
}

HeroMatrix4x4 heroMathTansponeM4x4(HeroMatrix4x4 A)
{
    HeroMatrix4x4 matrix;

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

HeroFloat4 heroMathMultiplyM4x4F4(HeroMatrix4x4 matrix, HeroFloat4 vector)
{
    float x = vector.x*matrix.col[0].x + vector.y*matrix.col[1].x + vector.z*matrix.col[2].x + vector.w*matrix.col[3].x;
    float y = vector.x*matrix.col[0].y + vector.y*matrix.col[1].y + vector.z*matrix.col[2].y + vector.w*matrix.col[3].y;
    float z = vector.x*matrix.col[0].z + vector.y*matrix.col[1].z + vector.z*matrix.col[2].z + vector.w*matrix.col[3].z;
    float w = vector.x*matrix.col[0].w + vector.y*matrix.col[1].w + vector.z*matrix.col[2].w + vector.w*matrix.col[3].w;

    return (HeroFloat4){x, y, z, w};
}

float* heroMathM4x4ToArray(HeroMatrix4x4 A)
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

HeroMatrix4x4 heroMathArrayToM4x4(float* array)
{
    HeroMatrix4x4 result;

    result.col[0] = (HeroFloat4){array[0], array[4], array[8], array[12]};
    result.col[1] = (HeroFloat4){array[1], array[5], array[9], array[13]};
    result.col[2] = (HeroFloat4){array[2], array[6], array[10], array[14]};
    result.col[3] = (HeroFloat4){array[3], array[7], array[11], array[15]};

    return result;
}

void heroMathTranslateM4x4(HeroMatrix4x4* matrix, HeroFloat4 translation)
{
    matrix->col[3].x += translation.x;
    matrix->col[3].y += translation.y;
    matrix->col[3].z += translation.z;
}

void heroMathScaleM4x4(HeroMatrix4x4* matrix, HeroFloat4 scale)
{
    matrix->col[0].x = scale.x;
    matrix->col[1].y = scale.y;
    matrix->col[2].z = scale.z;
}

void heroMathRotateXM4x4(HeroMatrix4x4* matrix, float radians)
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

void heroMathRotateYM4x4(HeroMatrix4x4* matrix, float radians)
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

void heroMathRotateZM4x4(HeroMatrix4x4* matrix, float radians)
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

void heroMathRotateXYZM4x4(HeroMatrix4x4* matrix, HeroFloat4 rotation)
{
    if(rotation.x != 0.0f)
        heroMathRotateXM4x4(matrix, rotation.x);
    if(rotation.y != 0.0f)
        heroMathRotateYM4x4(matrix, rotation.y);
    if(rotation.z != 0.0f)
        heroMathRotateZM4x4(matrix, rotation.z);
}

HeroMatrix4x4 heroMathPixelScreenMatrix(int width, int height, float near, float far)
{
    HeroMatrix4x4 matrix = heroMat4x4Identity;
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = -2.0f/(far - near);
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = (far + near)/(far - near);
    matrix.col[3].w = 1;
    return matrix;
}

HeroMatrix4x4 heroMathProjectionMatrix(int width, int height, float FOV, float near, float far)
{
    float aspectRatio = (float)width/(float)height;
    float tg = tanf(FOV*0.5f*PI/180.0f);

    HeroMatrix4x4 matrix = heroMat4x4Identity;

    matrix.col[0].x = 1.0f/(aspectRatio*tg);
    matrix.col[1].y = 1.0f/tg;
    matrix.col[2].z = -far/(near - far);
    matrix.col[3].z = (far*near)/(near - far);

    return matrix;
}

HeroMatrix4x4 heroMathLookAtMatrix(HeroFloat3 eye, HeroFloat3 target, HeroFloat3 up)
{
    HeroFloat3 f = heroMathSubstractF3(target, eye);
    f = heroMathNormalizeF3(f);

    HeroFloat3 r = heroMathCrossProduct(f, up);
    r = (HeroFloat3){-r.x, -r.y, -r.z};
    r = heroMathNormalizeF3(r);

    HeroFloat3 u = heroMathCrossProduct(r, f);
    u = (HeroFloat3){-u.x, -u.y, -u.z};

    HeroMatrix4x4 matrix;

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

    matrix.col[3].x = -heroMathDotProductF3(r,eye);
    matrix.col[3].y = -heroMathDotProductF3(u,eye);
    matrix.col[3].z = -heroMathDotProductF3(f,eye);
    matrix.col[3].w = 1.0f;

    return matrix;
}

HeroMatrix4x4 heroMathOrthographicMatrix(int width, int height, float near, float far)
{
    HeroMatrix4x4 matrix = heroMat4x4Identity;
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = -2.0f/(far - near);
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = (far + near)/(far - near);
    matrix.col[3].w = 1;
    return matrix;
}