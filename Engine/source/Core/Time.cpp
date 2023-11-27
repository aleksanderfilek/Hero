#include"Time.hpp"
#include"../ThirdParty/SDL2/SDL.h"

namespace Hero
{
Time* Time::instance = nullptr;

HERO Time::Time()
{
    instance = this;
    startupTime = SDL_GetTicks();
}

HERO Time::~Time()
{
    
}

}