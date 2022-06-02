#pragma once

#include"IComponent.hpp"
#include"../Core/Sid.hpp"

#include<unordered_map>
#include<vector>

namespace Hero
{

class Actor
{
private:    
    class ComponentContext* context = nullptr;

    std::unordered_map<Sid, ChunkArrayIndex, SidHashFunction> components;

public:
    HERO Actor(class ComponentContext* Context);
    HERO ~Actor();

    HERO void AddComponent(const Sid& sid);
    HERO bool RemoveComponent(const Sid& sid);
    HERO IComponent* GetComponent(const Sid& sid);
    HERO std::vector<IComponent*> GetAllComponentsData();
    HERO std::vector<Sid> GetAllComponentsSid();

    inline class ComponentContext* GetComponentContext() const { return context; }
    inline uint32_t getComponentsCount(){ return components.size(); }
};


} 
