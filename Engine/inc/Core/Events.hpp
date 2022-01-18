#pragma once

#include<vector>

namespace Hero
{

typedef void (*EventFunction)(void* object, void *args, int argc);
#define event(name) void name(void* object, void *args, int argc)

class EventHandler
{
    private:    
        std::vector<EventFunction> functions;
        
    public:
        HERO EventHandler();
        HERO ~EventHandler();

        HERO void add(EventFunction function);
        HERO void clear();
        HERO void invoke(void* object, void *args, int argc);
};

}