#pragma once

#include"ISystem.hpp"
#include"ThirdParty.hpp"
#include"Sid.hpp"

#include<vector>

namespace Hero
{
namespace System
{

class Window;

class Event : public ISystem
{
private:
    SDL_Event sdlEvent;
    std::vector<Window*> windows;

public:
    HERO Event(const Sid& sid);
    HERO ~Event();

    HERO void init();
    HERO void update();
    HERO void close();

    HERO void addWindow(Window* window);
    HERO void removeWindow(Sid sid);
    HERO void clearWindows();
};
}
}