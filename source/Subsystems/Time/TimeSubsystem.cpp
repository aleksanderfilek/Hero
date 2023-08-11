#include "TimeSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"

TimeSubsystem* TimeSubsystem::instance = nullptr;

TimeSubsystem::TimeSubsystem()
{
    instance = this;
    updateEnabled = true;
}

void TimeSubsystem::Startup()
{
    if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
    {
        exit(-1);
    }

    startupTime = SDL_GetTicks();
}

void TimeSubsystem::Shutdown()
{
    for(Timer* timer: timers)
    {
        delete timer;
    }

    SDL_Quit();
}

void TimeSubsystem::Update()
{
    for(Timer* timer: timers)
    {
        timer->Update(scaledDeltaTime);
    }

    SetDeltaTime((float)(SDL_GetTicks() - timerTick) / 1000.0f);
    timerTick = SDL_GetTicks();
}

void TimeSubsystem::SetDeltaTime(float Value)
{
    deltaTime = Value;
    scaledDeltaTime = Value * timeScale;
}

void TimeSubsystem::SetScale(float Value)
{
    timeScale = Value;
    scaledDeltaTime = Value * deltaTime;
}

void TimeSubsystem::RemoveTimer(Timer* Timer)
{
    timers.Remove(Timer);
    delete Timer;
}