#include"ISystem.hpp"

namespace Hero
{

void ISystem::init()
{   
    inited = true;
    #ifdef HERO_DEBUG 
    std::cout<<"["<<sid.getName()<<"] - Initializing"<<std::endl; 
    #endif 
}

void ISystem::update(){};

void ISystem::close()
{ 
    #ifdef HERO_DEBUG 
    std::cout<<"["<<sid.getName()<<"] - Closing"<<std::endl; 
    #endif
}

void ISystem::printMessage(const std::string& msg)
{ 
    #ifdef HERO_DEBUG
    std::cout<<"["<<sid.getName()<<"] - "<<msg<<std::endl; 
    #endif
}

}