#pragma once

#include<iostream>
#include<vector>
#include<typeinfo>

namespace Hero
{

struct  Sid;
class ISystem;
class Time;

class Core
{
private:
    static Core* instance;

    std::vector<ISystem*> systems;
    bool running = false;

    Time* time;
public:
    Core();
    ~Core();

    void start();
    inline static void close(){ Core::instance->running = false; }
    inline static bool isRunning(){ return Core::instance->running; }

    static Core* get(){ return instance; }

    bool addSystem(ISystem* newSystem);
    bool removeSystem(Sid sid);
    ISystem* getSystem(const Sid& sid);
};

}