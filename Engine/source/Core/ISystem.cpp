#include"ISystem.hpp"

#include<iostream>

namespace Hero
{

HERO void ISystem::init()
{   
    inited = true;
    #ifdef HERO_DEBUG 
    std::cout<<"["<<sid.getName()<<"] - Initializing"<<std::endl; 
    #endif 
}

HERO void ISystem::update(){};

HERO void ISystem::close()
{ 
    #ifdef HERO_DEBUG 
    std::cout<<"["<<sid.getName()<<"] - Closing"<<std::endl; 
    #endif
}

HERO void ISystem::printMessage(const std::string& msg)
{ 
    #ifdef HERO_DEBUG
    std::cout<<"["<<sid.getName()<<"] - "<<msg<<std::endl; 
    #endif
}

}