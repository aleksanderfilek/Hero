#include "InputSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../Core.h"

InputSubsystem* InputSubsystem::instance = nullptr;

InputSubsystem::InputSubsystem()
{
    instance = this;
    updateEnabled = true;
}

void InputSubsystem::Startup()
{
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    {
        exit(-1);
    }
}

void InputSubsystem::Shutdown()
{
    SDL_Quit();
}

void InputSubsystem::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0 )
    {
        if(event.type == SDL_QUIT )
        {
            Core::Get().Stop();
        }
    }
}