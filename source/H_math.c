#include"H_math.h"

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