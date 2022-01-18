#pragma once

#include"Sid.hpp"

#include<iostream>

namespace Hero
{
class Core;

class ISystem
{
friend class Core;

protected:
    bool inited = false;
    Sid sid;
    uint32_t priority = 127;

public:
    ISystem(const Sid& _sid):sid(_sid){}
    virtual ~ISystem(){};

    HERO virtual void init();
    HERO virtual void update();
    HERO virtual void close();

    HERO void printMessage(const std::string& msg);

    inline std::string getName() { return sid.getName(); }
    inline Sid getSid(){ return sid; }
    uint32_t getPriority(){ return priority; }
};

}