#include"Event.hpp"
#include"Window.hpp"

#include<sstream>


namespace Hero
{
namespace System
{

Event::Event(const Sid& sid) : ISystem(sid)
{

}

Event::~Event()
{

}

void Event::init()
{
    ISystem::init();
}

void Event::update()
{
    while(SDL_PollEvent(&sdlEvent) != 0){
        for(auto window: windows)
        {
            window->handleEvents(&sdlEvent);
        }
    }
}

void Event::close()
{
    ISystem::close();
    windows.clear();
}

void Event::addWindow(Window* window)
{
    #ifdef HERO_DEBUG
    for(auto win: windows)
    {
        if(win->getSid() == window->getSid())
        {
            std::stringstream ss;
            ss<<"Can not add window with name: "<<window->getName() <<" Window already registred!";
            printMessage(ss.str());
            return;
        }
    }
    #endif

    windows.push_back(window);
}

void Event::removeWindow(Sid sid)
{
    int index = 0;
    for(auto win: windows)
    {
        if(win->getSid() == sid)
        {
            break;
        }

        index++;
    }

    #ifdef HERO_DEBUG
    if(index == windows.size())
    {
        std::stringstream ss;
        ss<<"Can not remove window with name: "<<sid.getName() <<" Window is not registred!";
        printMessage(ss.str());
        return;
    }
    #endif

    windows.erase(windows.begin() + index);
}

void Event::clearWindows()
{
    windows.clear();
}

}
}