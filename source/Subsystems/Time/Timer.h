#pragma once

#include "../../Definitions.h"
#include "../../GenericTypes/Event.h"

EVENT_DISPATCHER(TimerEvent)

class HERO_API Timer
{
friend class TimeSubsystem;

private:
    class TimeSubsystem* timeSubsystem = nullptr;

    float currentTime = 0.0;
    float period = 0.0f;
    bool loop = false;
    bool paused = false;
    TimerEvent onTimer;

    void Update(float DeltaTime);

public:
    void Pause();
    void Unpause();
};