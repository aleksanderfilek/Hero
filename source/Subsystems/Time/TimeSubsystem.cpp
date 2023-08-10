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
    startupTime = SDL_GetTicks();
}

void TimeSubsystem::Shutdown()
{

}

void TimeSubsystem::Update()
{
    SetDeltaTime((double)(SDL_GetTicks() - timerTick) / 1000.0);
    timerTick = SDL_GetTicks();
}

void TimeSubsystem::SetDeltaTime(double Value)
{
    deltaTime = Value;
    scaledTime = Value * timeScale;
}

void TimeSubsystem::SetScale(double Value)
{
    timeScale = Value;
    scaledTime = Value * deltaTime;
}