#ifndef HERO_SYSTEM_HPP
#define HERO_SYSTEM_HPP

#include<cstdint>
#include<iostream>

#include"Hero_Utilities.hpp"

namespace Hero
{
class Core;

class ISystem
{
friend class Core;

private:
    bool _inited = false;

public:
    ISystem(){}
    virtual ~ISystem(){};

    virtual const char* GetName() = 0;

    virtual void Init()
    {   this->_inited = true;
        DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - Initializing"<<std::endl; ) 
    }

    virtual void Update() = 0;

    virtual void Close()
    { DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - Closing"<<std::endl; ) }
    
    virtual std::uint8_t priority(){ return 127; }

    inline void PrintMessage(const char* msg)
    { DEBUG_CODE( std::cout<<"["<<this->GetName()<<"] - "<<msg<<std::endl; ) }
};

}

#endif