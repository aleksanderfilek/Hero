#pragma once

#include "../Definitions.h"

class HERO_API Intersection
{
public:
    template<typename Vec2>
    static bool PointToRectangle(const Vec2& Point, const Vec2& RectPosition, const Vec2& RectSize)
    {
        if(Point.X < RectPosition.X || Point.Y < RectPosition.Y)
            return false;

        if(Point.X > RectPosition.X + RectSize.X || Point.Y > RectPosition.Y + RectSize.Y)
            return false;

        return true;
    }
};