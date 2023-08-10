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
    double deltaTime = 0.0;
    double timeScale = 1.0;
    double scaledTime = 0.0;

    void SetDeltaTime(double Value);

public:
    static TimeSubsystem& Get() { return *instance; }

    TimeSubsystem();

    virtual void Startup() override;
    virtual void Shutdown() override;
    virtual void Update() override;

    void SetScale(double Value);

private:
    Array<class Timer*> timers;

public:
    template<class UserClass>
    Timer* AddTimer(UserClass* object, void (UserClass::*methodPtr)(), float period = 1.0f, bool loop = false)
    {
        Timer* timer = new Timer();
        timer->currentTime = 0.0;
        timer->period = period;
        timer->loop = loop;
        timer->onTimer.addEvent(object, methodPtr);
    }
};