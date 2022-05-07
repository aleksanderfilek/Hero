#pragma once

#include"../Core/ISystem.hpp"
#include"../ThirdParty/SDL2/SDL.h"
#include"../Core/Sid.hpp"

#include<vector>

namespace Hero
{
namespace System
{

class Event : public ISystem
{
private:
    SDL_Event sdlEvent;
    std::vector<class Window*> windows;

public:
    HERO Event(const Sid& sid);
    HERO ~Event();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO void addWindow(class Window* window);
    HERO void removeWindow(Sid sid);
    HERO void clearWindows();
};
}
}