#include"ComponentContext.hpp"
#include"IComponent.hpp"
#include"../Systems/Profiler.hpp"

#include <iostream>

namespace Hero
{

HERO ComponentContext::~ComponentContext()
{
  Clear();
}

HERO void ComponentContext::Update()
{
  for(auto& system: systems)
  {
    uint64_t start = System::Profiler::GetTime();
    system.second->update();
    uint64_t end = System::Profiler::GetTime();
    System::Profiler::Register(system.first, end - start);
  }
}

HERO void ComponentContext::Register(const Sid& sid, IComponentSystemHandle* system)
{
  if(systems.find(sid) != systems.end())
  {
    #ifdef HERO_DEBUG
    std::cout<<"[ComponentContext] - ComponentSystem with sid: "<<sid<<" aleardy exists in the context."<<std::endl;
    #endif
    return;
  }

  bool result = systems.insert({sid, system}).second;
  if(!result)
  {
    #ifdef HERO_DEBUG
    std::cout<<"[ComponentContext] - Could not add system with sid: "<<sid<<" to the context."<<std::endl;
    #endif
  }
}

HERO void ComponentContext::Unregister(const Sid& sid)
{
  if(systems.find(sid) == systems.end())
  {
    #ifdef HERO_DEBUG
    std::cout<<"[ComponentContext] - ComponentSystem with sid: "<<sid<<" aleardy exists in the context."<<std::endl;
    #endif
    return;
  }

  systems.erase(sid);
}

HERO IComponentSystemHandle* ComponentContext::Get(const Sid& sid) const
{
  auto system = systems.find(sid);
  if(system == systems.end())
  {
    #ifdef HERO_DEBUG
    std::cout<<"[ComponentContext] - ComponentSystem with sid: "<<sid<<" aleardy exists in the context."<<std::endl;
    #endif
    return nullptr;
  }

  return system->second;
}

HERO void ComponentContext::Clear()
{
  systems.clear();
}

}