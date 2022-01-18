#pragma once

#include<iostream>
#include<vector>
#include<typeinfo>

#ifdef _WIN32
    #define HeroMain WinMain
#else
    #define HeroMain main
#endif

namespace Hero
{

struct  Sid;
class ISystem;
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
    HERO ISystem* getSystem(const Sid& sid);
};

}