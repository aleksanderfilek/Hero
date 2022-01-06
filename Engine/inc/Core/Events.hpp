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
        EventHandler();
        ~EventHandler();

        void add(EventFunction function);
        void clear();
        void invoke(void* object, void *args, int argc);
};

}