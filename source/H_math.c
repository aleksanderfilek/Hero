#include"H_math.h"
#include<math.h>

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

HeroMat4x4 heroMathOrthographicMatrix(int width, int height, float near, float far)
{
    HeroMat4x4 matrix = heroMat4x4Identity;
    matrix.col[0].x = 2.0f/width;
    matrix.col[1].y = -2.0f/height;
    matrix.col[2].z = -2.0f/(far - near);
    matrix.col[3].x = -1;
    matrix.col[3].y = 1;
    matrix.col[3].z = (far + near)/(far - near);
    matrix.col[3].w = 1;
    return matrix;
}