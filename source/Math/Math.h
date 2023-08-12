#pragma once

#include "MathConstants.h"
#include "Int2.h"
#include "Int3.h"
#include "Int4.h"
#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include "Quaternion.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

template<typename T>
T min(T a, T b)
{
    return (a < b) ? a : b;
}

template<typename T>
T max(T a, T b)
{
    return (a > b) ? a : b;
}

template<typename T>
T Clamp(T Value, T Min, T Max)
{
    return (Value < Min) ? Min : (Value > Max) ? Max : Value;
}

HERO_API float Deg2Rad(float Degree);
HERO_API float Rad2Deg(float Radians);
HERO_API float Lerp(float A, float B, float Alpha);