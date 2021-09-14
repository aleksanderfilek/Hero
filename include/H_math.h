#ifndef HERO_MATH_H_
#define HERO_MATH_H_

#define PI 3.141596f

typedef struct
{
    int x, y;
} HeroInt2;

typedef struct
{
    int x, y, z;
} HeroInt3;

typedef struct
{
    int x, y, z, w;
} HeroInt4;

typedef struct
{
    float x, y;
} HeroFloat2;

typedef struct
{
    float x, y, z;
} HeroFloat3;

typedef struct
{
    float x, y, z, w;
} HeroFloat4;

typedef struct
{
    HeroFloat4 col[4];
} HeroMat4x4;
#define heroMat4x4Identity {{{1.0f,0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f,0.0f},{0.0f,0.0f,1.0f,0.0f},{0.0f,0.0f,0.0f,1.0f}}}

#ifdef __cplusplus
extern "C" {
#endif

extern float deg2rad(float degree);
extern float rad2deg(float radians);
extern HeroMat4x4 heroMathOrthographicMatrix(int width, int height, float near, float far);


#ifdef __cplusplus
}
#endif

#endif