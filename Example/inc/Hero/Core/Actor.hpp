#pragma once

#include<unordered_map>
#include<typeinfo>
#include<iostream>

namespace Hero
{
class IComponent;
class IComponentSystemHandler;

class Actor
{
private:
    std::unordered_map<IComponentSystemHandler* ,IComponent*> components;

public:
    HERO ~Actor();

    template<class T>
    IComponent* getComponent()
    {
        auto result = components.find(T::get());
        if(result == components.end()) return nullptr;

        return result->second;
    }

    template<class T>
    IComponent* addComponent()
    {
        IComponent* component = T::get()->addComponent(this);
        components.insert({T::get(), component});
        return component;
    }

    template<class T>
    void removeComponent()
    {
        auto result = components.find(T::get());
        if(result == components.end()) return;

        T::get()->removeComponent(result->second);
        components.erase(result);
    }

    inline uint32_t getComponentsCount(){ return components.size(); }
};

} 
