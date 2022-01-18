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
    Event(const Sid& sid);
    ~Event();

    void init();
    void update();
    void close();

    void addWindow(Window* window);
    void removeWindow(Sid sid);
    void clearWindows();
};
}
}