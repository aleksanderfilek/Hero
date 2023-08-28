#pragma once

#include "../../Definitions.h"
#include "Controls/Canvas.h"

class HERO_API Widget
{
private:
    Canvas canvas;

public:
    virtual void Construct();

    virtual void Update(float ElapsedTime);
};