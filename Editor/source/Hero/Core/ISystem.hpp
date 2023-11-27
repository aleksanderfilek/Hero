#pragma once

#include"Sid.hpp"

namespace Hero
{
class Core;

class HERO ISystem
{
friend class Core;

protected:
    bool inited = false;
    Sid sid;
    uint32_t priority = 127;

public:
    ISystem(const Sid& _sid):sid(_sid){}
    virtual ~ISystem(){};

    virtual void init();
    virtual void update();
    virtual void close();

    void printMessage(const std::string& msg);

    inline std::string getName() { return sid.getName(); }
    inline Sid getSid(){ return sid; }
    uint32_t getPriority(){ return priority; }
};

}