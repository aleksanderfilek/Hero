#include "Math.h"

HERO_API float Deg2Rad(float Degree)
{
    return (Degree * PI) / 180.0f;
}

HERO_API float Rad2Deg(float Radians)
{
    return (180.0f * Radians) / PI;
}

HERO_API float Lerp(float A, float B, float Alpha)
{
    return (1.0f - Alpha) * A + Alpha * B;
}