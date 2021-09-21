#ifndef HERO_MATH_H_
#define HERO_MATH_H_

#define PI 3.141596f

typedef struct
{
    int x, y;
} HeroInt2;

#define heroInt2zero (HeroInt2){0, 0}
#define heroInt2one (HeroInt2){1, 1}

typedef struct
{
    int x, y, z;
} HeroInt3;

#define heroInt3zero (HeroInt3){0, 0, 0}
#define heroInt3one (HeroInt3){1, 1, 1}

typedef struct
{
    int x, y, z, w;
} HeroInt4;

#define heroHeroInt4zero (HeroInt4){0, 0, 0, 0}
#define heroHeroInt4one (HeroInt4){1, 1, 1, 1}

typedef struct
{
    float x, y;
} HeroFloat2;

#define heroFloat2zero (HeroFloat2){0.0f, 0.0f}
#define heroFloat2one (HeroFloat2){1.0f, 1.0f}

typedef struct
{
    float x, y, z;
} HeroFloat3;

#define heroFloat3zero (HeroFloat3){0.0f, 0.0f, 0.0f}
#define heroFloat3one (HeroFloat3){1.0f, 1.0f, 1.0f}

typedef struct
{
    float x, y, z, w;
} HeroFloat4;

#define heroFloat4zero (HeroFloat4){0.0f, 0.0f, 0.0f, 0.0f}
#define heroFloat4one (HeroFloat4){1.0f, 1.0f, 1.0f, 1.0f}

typedef struct
{
    HeroFloat2 col[2];
} HeroMatrix2x2;

#define matrix2x2identity (HeroMatrix2x2){(HeroFloat2){1.0f,0.0f},(HeroFloat2){0.0f,1.0f}}

typedef struct
{
    HeroFloat3 col[3];
} HeroMatrix3x3;

#define matrix3x3identity (HeroMatrix3x3){(HeroFloat3){1.0f,0.0f,0.0f},(HeroFloat3){0.0f,1.0f,0.0f},(HeroFloat3){0.0f,0.0f,1.0f}}

typedef struct
{
    HeroFloat4 col[4];
} HeroMatrix4x4;

#define heroMat4x4Identity (HeroMatrix4x4){(HeroFloat4){1.0f,0.0f,0.0f,0.0f},(HeroFloat4){0.0f,1.0f,0.0f,0.0f},(HeroFloat4){0.0f,0.0f,1.0f,0.0f},(HeroFloat4){0.0f,0.0f,0.0f,1.0f}}

#ifdef __cplusplus
extern "C" {
#endif

extern float heroMathDeg2rad(float degree);
extern float heroMathRad2deg(float radians);
extern int heroMathClampI(int value, int min, int max);
extern float heroMathClampF(float value, float min, float max);

extern HeroInt2 heroMathAddI2(HeroInt2 A, HeroInt2 B);
extern HeroInt2 heroMathSubstractI2(HeroInt2 A, HeroInt2 B);
extern int heroMathDotProductI2(HeroInt2 A, HeroInt2 B);
extern float heroMathDistanceI2(HeroInt2 A, HeroInt2 B);

extern HeroInt3 heroMathAddI3(HeroInt3 A, HeroInt3 B);
extern HeroInt3 heroMathSubstract(HeroInt3 A, HeroInt3 B);
extern int heroMathDotProductI3(HeroInt3 A, HeroInt3 B);
extern float heroMathDistanceI3(HeroInt3 A, HeroInt3 B);

extern HeroInt4 heroMathAddI4(HeroInt4 A, HeroInt4 B);
extern HeroInt4 heroMathSubstractI4(HeroInt4 A, HeroInt4 B);

extern float heroMathLerpF(float a, float b, float t);

extern HeroFloat2 heroMathAddF2(HeroFloat2 A,HeroFloat2 B);
extern HeroFloat2 heroMathSubstractF2(HeroFloat2 A,HeroFloat2 B);
extern float heroMathDotProductF2(HeroFloat2 A,HeroFloat2 B);
extern HeroFloat2 heroMathMultiplyF2(HeroFloat2 A, float k);
extern HeroFloat2 heroMathNormalizeF2(HeroFloat2 A);
extern float heroMathLengthF2(HeroFloat2 A);
extern float heroMathDistanceF2(HeroFloat2 A, HeroFloat2 B);

extern HeroFloat3 heroMathAddF3(HeroFloat3 A, HeroFloat3 B);
extern HeroFloat3 heroMathSubstractF3(HeroFloat3 A, HeroFloat3 B);
extern float heroMathDotProductF3(HeroFloat3 A, HeroFloat3 B);
extern HeroFloat3 heroMathCrossProduct(HeroFloat3 A, HeroFloat3 B);
extern HeroFloat3 heroMathMultiplyF3(HeroFloat3 A, float k);
extern HeroFloat3 heroMathNormalizeF3(HeroFloat3 A);
extern float heroMathLengthF3(HeroFloat3 A);
extern HeroFloat3 heroMathLerpF3(HeroFloat3 A, HeroFloat3 B, float t);
extern float heroMathDistanceF3(HeroFloat3 A, HeroFloat3 B);

extern HeroFloat4 heroMathAddF4(HeroFloat4 A, HeroFloat4 B);
extern HeroFloat4 heroMathSubstractF4(HeroFloat4 A, HeroFloat4 B);
extern HeroFloat4 heroMathMultiplyF4(HeroFloat4 A, float k);
extern HeroFloat4 heroMathNormalizeF4(HeroFloat4 A);
extern float heroMathLengthF4(HeroFloat4 A);

extern HeroMatrix2x2 heroMathMultiplyM2x2(HeroMatrix2x2 A, HeroMatrix2x2 B);
extern float heroMathDeterminentM2x2(HeroMatrix2x2 A);
extern HeroMatrix2x2 heroMathTansponeM2x2(HeroMatrix2x2 A);
extern HeroMatrix2x2 heroMathInvertM2x2(HeroMatrix2x2 A);
extern HeroFloat2 heroMathMultiplyM2x2F2(HeroMatrix2x2 matrix, HeroFloat2 vector);

extern HeroMatrix3x3 heroMathMultiplyM3x3(HeroMatrix3x3 A, HeroMatrix3x3 B);
extern float heroMathDeterminentM3x3(HeroMatrix3x3 A);
extern HeroMatrix3x3 heroMathTansponeM3x3(HeroMatrix3x3 A);
extern HeroMatrix3x3 heroMathInvertM3x3(HeroMatrix3x3 A);
extern HeroFloat3 heroMathMultiplyM3x3F3(HeroMatrix3x3 matrix, HeroFloat3 vector);

extern HeroMatrix4x4 heroMathMultiplyM4x4(HeroMatrix4x4 A, HeroMatrix4x4 B);
extern float heroMathDeterminentM4x4(HeroMatrix4x4 A);
extern HeroMatrix4x4 heroMathTansponeM4x4(HeroMatrix4x4 A);
extern HeroMatrix4x4 heroMathInvertM4x4(HeroMatrix4x4 A);
extern HeroFloat4 heroMathMultiplyM4x4F4(HeroMatrix4x4 matrix, HeroFloat4 vector);
extern float* heroMathM4x4ToArray(HeroMatrix4x4 A);
extern HeroMatrix4x4 heroMathArrayToM4x4(float* array);

extern void heroMathTranslateM4x4(HeroMatrix4x4* matrix, HeroFloat4 translation);
extern void heroMathScaleM4x4(HeroMatrix4x4* matrix, HeroFloat4 scale);
extern void heroMathRotateXM4x4(HeroMatrix4x4* matrix, float radians);
extern void heroMathRotateYM4x4(HeroMatrix4x4* matrix, float radians);
extern void heroMathRotateZM4x4(HeroMatrix4x4* matrix, float radians);
extern void heroMathRotateXYZM4x4(HeroMatrix4x4* matrix, HeroFloat4 rotation);

extern HeroMatrix4x4 heroMathPixelScreenMatrix(int width, int height, float near, float far);

extern HeroMatrix4x4 heroMathProjectionMatrix(int width, int height, float FOV, float near, float far);
extern HeroMatrix4x4 heroMathLookAtMatrix(HeroFloat3 eye, HeroFloat3 target, HeroFloat3 up);
extern HeroMatrix4x4 heroMathOrthographicMatrix(int width, int height, float near, float far);

#ifdef __cplusplus
}
#endif

#endif