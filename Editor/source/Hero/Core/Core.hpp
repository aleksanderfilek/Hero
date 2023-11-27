#pragma once

#include"Sid.hpp"
#include"ISystem.hpp"

#include<vector>
#include<typeinfo>

#ifdef _WIN32
    #define HeroMain SDL_main
#else
    #define HeroMain main
#endif

namespace Hero
{

class Time;

class HERO Core
{
private:
    static Core* instance;

    std::vector<ISystem*> systems;
    bool running = false;

    Time* time;
public:
    HERO Core();
    HERO ~Core();

    HERO void start();
    inline static void close(){ Core::instance->running = false; }
    inline static bool isRunning(){ return Core::instance->running; }

    static Core* get(){ return instance; }

    HERO bool addSystem(ISystem* newSystem);
    HERO bool removeSystem(Sid sid);
    template<class T>
    static T* getSystem(const Sid& sid)
    {
        for(ISystem* sys: instance->systems)
        {
            if(sid == sys->sid)
            {
                return (T*)sys;
            }
        }
        return nullptr;
    }
};

}