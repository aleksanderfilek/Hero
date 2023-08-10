#pragma once

#include "../../Definitions.h"
#include "../../GenericTypes/Event.h"

EVENT_DISPATCHER(TimerEvent)

class HERO_API Timer
{
friend class TimeSubsystem;

private:
    double currentTime = 0.0;
    float period = 0.0f;
    bool loop = false;
    TimerEvent onTimer;

    void Update(double DeltaTime);

public:
    void Pause();
    void Reset();
};