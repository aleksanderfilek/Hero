#include"Time.hpp"

#include"ThirdParty.hpp"

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