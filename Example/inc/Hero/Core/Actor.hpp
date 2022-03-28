#pragma once

#include"IComponent.hpp"
#include"Transform.hpp"
#include"Sid.hpp"

#include<unordered_map>

namespace Hero
{

class Actor
{
private:    
    class ComponentContext* context = nullptr;

    std::unordered_map<Sid, ChunkArrayIndex, SidHashFunction> components;

public:
    HERO Actor(ComponentContext* Context);
    HERO ~Actor();

    HERO void AddComponent(const Sid& sid);
    HERO bool RemoveComponent(const Sid& sid);
    HERO IComponent* GetComponent(const Sid& sid);

    inline uint32_t getComponentsCount(){ return components.size(); }
};


} 
