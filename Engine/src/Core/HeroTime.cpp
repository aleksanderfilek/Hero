#include"Core/HeroTime.hpp"

#include"ThirdParty.hpp"

namespace Hero
{
    Time* Time::instance = nullptr;

    Time::Time()
    {
        instance = this;
        startupTime = SDL_GetTicks();
    }

    Time::~Time()
    {
        
    }

}