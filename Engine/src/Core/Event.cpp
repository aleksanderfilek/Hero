#include"Event.hpp"

#include<stdlib.h>

namespace Hero
{

EventHandler::EventHandler()
{

}

EventHandler::~EventHandler()
{
    clear();
}

void EventHandler::add(EventFunction function)
{
    functions.push_back(function);
}

void EventHandler::clear()
{
    functions.clear();
}

void EventHandler::invoke(void* object, void *args, int argc)
{
    for(auto func: functions)
    {
        func(object, args, argc);
    }
}

}