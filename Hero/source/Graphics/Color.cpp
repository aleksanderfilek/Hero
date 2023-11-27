#include "Color.h"

Float4 Color::ToFloat4() const
{
    return { (float)R / 255.0f,
            (float)G / 255.0f,
            (float)B / 255.0f,
            (float)A / 255.0f
    };
}