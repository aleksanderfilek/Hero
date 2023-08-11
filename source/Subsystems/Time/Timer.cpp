#include "Timer.h"
#include "TimeSubsystem.h"

void Timer::Update(float DeltaTime)
{
    if(paused)
        return;

    currentTime += DeltaTime;
    if(currentTime >= period)
    {
        onTimer.Broadcast();
        currentTime -= period;
        if(!loop)
        {
            timeSubsystem->RemoveTimer(this);
        }
    }
}

void Timer::Pause()
{
    paused = true;
}

void Timer::Unpause()
{
    paused = false;
}