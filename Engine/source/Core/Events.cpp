#include"Events.hpp"

#include<cstdlib>

namespace Hero
{

HERO EventHandler::EventHandler()
{

}

HERO EventHandler::~EventHandler()
{
    clear();
}

HERO void EventHandler::add(EventFunction function)
{
    functions.push_back(function);
}

HERO void EventHandler::clear()
{
    functions.clear();
}

HERO void EventHandler::invoke(void* object, void *args, int argc)
{
    for(auto func: functions)
    {
        func(object, args, argc);
    }
}

}