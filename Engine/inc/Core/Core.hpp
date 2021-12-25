#pragma once

#include<iostream>
#include<vector>
#include<typeinfo>

#include"HeroSid.hpp"
#include"HeroSystem.hpp"
#include"HeroTime.hpp"

namespace Hero
{

class Core
{
private:
    static Core* instance;

    std::vector<ISystem*> systems;
    bool running = false;

    Time time;
public:
    Core();
    ~Core();

    void start();
    inline static void close(){ Core::instance->running = false; }
    inline static bool isRunning(){ return Core::instance->running; }

    static Core* get(){ return instance; }

    bool addSystem(ISystem* newSystem);
    bool removeSystem(Sid sid);

    static ISystem* getSystem(Sid sid)
    {
        for(ISystem* sys: instance->systems)
        {
            if(sid == sys->sid)
            {
                return sys;
            }
        }

        return nullptr;
    }
};

}