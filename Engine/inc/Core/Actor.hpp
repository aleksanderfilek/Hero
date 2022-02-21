#pragma once

#include<unordered_map>
#include<typeinfo>
#include<iostream>
#include"IComponent.hpp"

namespace Hero
{

class Actor
{
private:
    std::unordered_map<IComponentSystemHandle* ,ChunkArrayIndex> components;

public:
    HERO Actor();
    HERO ~Actor();

    virtual void begin() = 0;
    virtual void update() = 0;
    virtual void close() = 0;

    template<class T>
    IComponent* getComponent()
    {
        auto result = components.find(T::get());
        if(result == components.end()) return nullptr;

        return T::get()->getComponent(result->second);
    }

    template<class T>
    void addComponent()
    {
        ChunkArrayIndex index = T::get()->addComponent(this);
        components.insert({T::get(), index});
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
