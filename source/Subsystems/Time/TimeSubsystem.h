#pragma once

#include "../Subsystem.h"
#include "../../Containers/Array.h"
#include "Timer.h"
#include <cstdint>

class HERO_API TimeSubsystem : public Subsystem
{
private:
    static TimeSubsystem* instance;

    uint32_t startupTime = 0;
    uint32_t timerTick = 0;
    float deltaTime = 0.0;
    float timeScale = 1.0;
    float scaledDeltaTime = 0.0;

    void SetDeltaTime(float Value);

public:
    static TimeSubsystem& Get() { return *instance; }

    TimeSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;

    void SetScale(float Value);
    float GetDeltaTime() const;

private:
    Array<class Timer*> timers;

public:
    template<class UserClass>
    Timer* AddTimer(UserClass* Object, void (UserClass::*MethodPtr)(), float period = 1.0f, bool loop = false)
    {
        Timer* timer = new Timer();
        timer->timeSubsystem = this;
        timer->currentTime = 0.0;
        timer->period = period;
        timer->loop = loop;
        timer->onTimer.AddEvent(Object, MethodPtr);
        timers.Add(timer);
    }

    void RemoveTimer(Timer* Timer);
};