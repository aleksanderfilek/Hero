#pragma once 

#include"../Utility/ChunkArray.hpp"

#include<cstdint>
#include<utility>
#include<iostream>

namespace Hero
{

class Actor;
class IComponentSystemHandler;

struct IComponent
{
    Actor* actor = nullptr;
    uint32_t index = 0;
};


class IComponentSystemHandle
{
public:
    virtual ChunkArrayIndex addComponent(Actor* owner) = 0;
    virtual void removeComponent(const ChunkArrayIndex& index) = 0;
    virtual IComponent* getComponent(const ChunkArrayIndex& index) = 0;
    virtual void update() = 0;
};

template<class T>
class IComponentSystem : public IComponentSystemHandle
{
    friend struct IComponent;

private:
    virtual void dataInit(T* data){}
    virtual void dataUpdate(T* data){}
    virtual void dataDestroy(T* data){}

protected:
    ChunkArray<T> data;

public:
    IComponentSystem(uint32_t chunkSize);
    ~IComponentSystem();

    void update() override;

    ChunkArrayIndex addComponent(Actor* owner) override;
    void removeComponent(const ChunkArrayIndex& index) override;
    IComponent* getComponent(const ChunkArrayIndex& index) override;
};


template<class T>
IComponentSystem<T>::IComponentSystem(uint32_t chunkSize) 
: data(chunkSize){}


template<class T>
IComponentSystem<T>::~IComponentSystem()
{
    for(auto& component: data)
    {
        if(component.first == false)
            continue;
            
        dataDestroy(&component.second);
    }

    data.clear();
}

template<class T>
void IComponentSystem<T>::update()
{
    for(auto& component: data)
    {
        if(component.first == false)
            continue;

        dataUpdate(&component.second);
    }
} 

template<class T>
ChunkArrayIndex IComponentSystem<T>::addComponent(Actor* owner)
{
    T t{};
    t.actor = owner;
    ChunkArrayIndex index = data.add(t);
    dataInit(&(data[index]));
    return index;
}

template<class T>
void IComponentSystem<T>::removeComponent(const ChunkArrayIndex& index)
{
    dataDestroy(&(data[index]));
    data.remove(index);
}

template<class T>
IComponent* IComponentSystem<T>::getComponent(const ChunkArrayIndex& index)
{
    return &(data[index]);
}

}