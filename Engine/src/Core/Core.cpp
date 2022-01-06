#include"Core.hpp"
#include"Sid.hpp"
#include"Time.hpp"
#include"ISystem.hpp"
#include"ThirdParty.hpp"

namespace Hero
{

Core* Core::instance = nullptr;

Core::Core()
{
    #ifdef HERO_DEBUG
    std::cout<<"[Core] - Initializing"<<std::endl;
    #endif

    Core::instance = this;

     // Initialize SDL
    if(SDL_Init(SDL_INIT_TIMER) < 0){
        std::cout<<"[Core] - SDL could not initialize! SDL Error: "<<SDL_GetError()<<std::endl;
        exit(-1);
    }
}

Core::~Core()
{
    #ifdef HERO_DEBUG
    std::cout<<"[Core] - Closing"<<std::endl;
    #endif

    for(ISystem* sys: systems)
    {
        delete sys;
    }
    systems.clear();

    SDL_Quit();
}

void Core::start()
{
    #ifdef HERO_DEBUG
    std::cout<<"[Core] - Starting"<<std::endl;
    #endif

    running = true;

    for(ISystem* sys: systems)
    {
        sys->init();
    }

    std::uint32_t timer;
    double deltaTime = 0.0;

    while (running)
    {
        timer = SDL_GetTicks();

        for(ISystem* sys: systems)
        {
            sys->update();
        }

        deltaTime = (double)(SDL_GetTicks() - timer)/1000.0;
        time->setDeltaTime(deltaTime);
    }


    std::vector<ISystem*>::iterator i = systems.end();
    while (i != systems.begin())
    {
        --i;
        (*i)->close();
    } 
}

bool Core::addSystem(ISystem* newSystem)
{
    #ifdef HERO_DEBUG
    if(running)
    {
        std::cout<<"[Core] - Can not add system while core is running!"<<std::endl;
        return false;
    }

    for(ISystem* sys: systems)
    {
        if(newSystem->sid == sys->sid)
        {
            std::cout<<"[Core] - System with name "<<newSystem->getName()<<" already exists!"<<std::endl;
            return false;
        }
    }
    #endif
    
    int index;
    for(index = 0; index < systems.size(); index++)
    {
        if(newSystem->getPriority() <= systems[index]->getPriority())
        {
            break;
        }
    }

    systems.insert(systems.begin() + index, newSystem);

    #ifdef HERO_DEBUG
    std::cout<<"[Core] - "<<newSystem->getName()<<" successfully added"<<std::endl;
    #endif

    return true;
}

bool Core::removeSystem(Sid sid)
{
    int index; 
    for(index = 0; index < systems.size(); index++)
    {
        if(sid == systems[index]->sid)
        {
            break;
        }
    }

    #ifdef HERO_DEBUG
    if(index == systems.size())
    {
        std::cout<<"[Core] - "<<systems[index]->getName()<<" does not exist and could not be deleted"<<std::endl;
        return false;
    }
    #endif
    
    ISystem*& system = systems[index];

    if(system->inited)
    {
        system->close();
    }

    Sid oldSid = systems[index]->sid;
    delete system;
    systems.erase(systems.begin() + index);

    #ifdef HERO_DEBUG
    std::cout<<"[Core] - "<<oldSid.getName()<<" successfully removed"<<std::endl;
    #endif

    return true;
}

ISystem* Core::getSystem(const Sid& sid)
{
    for(ISystem* sys: systems)
    {
        if(sid == sys->sid)
        {
            return sys;
        }
    }

    return nullptr;
}

}