#pragma once

#include"HeroSid.hpp"

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
    ISystem(Sid _sid):sid(_sid){}
    virtual ~ISystem(){};

    inline std::string getName() { return sid.getName(); }
    inline Sid getSid(){ return sid; }

    virtual void init()
    {   
        inited = true;
        #ifdef HERO_DEBUG 
        std::cout<<"["<<sid.getName()<<"] - Initializing"<<std::endl; 
        #endif 
    }

    virtual void update(){};

    virtual void close()
    { 
        #ifdef HERO_DEBUG 
        std::cout<<"["<<sid.getName()<<"] - Closing"<<std::endl; 
        #endif
    }
    
    uint32_t getPriority(){ return priority; }

    inline void printMessage(const std::string& msg)
    { 
        #ifdef HERO_DEBUG
        std::cout<<"["<<sid.getName()<<"] - "<<msg<<std::endl; 
        #endif
    }
};

}