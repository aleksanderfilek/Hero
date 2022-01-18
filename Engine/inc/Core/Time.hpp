#pragma once

#include<stdint.h>

namespace Hero
{
class Core;

class Time
{
    friend class Core;

private:
    static Time* instance;

    uint32_t startupTime;
    double deltaTime = 0.0;
    double timeScale = 1.0;
    double scaledTime = 0.0;

    void setDeltaTime(double value)
    { 
        deltaTime = value; 
        scaledTime = value * timeScale;
    }

public:
    Time();
    ~Time();

    HERO inline static double getDeltaTime()
    { 
        return instance->scaledTime; 
    }

    HERO inline static void setScale(double value)
    { 
        instance->timeScale = value; 
        instance->scaledTime = value * instance->deltaTime;
    }

    HERO inline static double getScale()
    { 
        return instance->timeScale; 
    }

    HERO inline static uint32_t getStartupTime()
    {
        return instance->startupTime;
    }
};

}