#pragma once 

#include<Utility/ChunkArray.hpp>
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
class HERO IComponentSystem : public IComponentSystemHandle
{
    friend struct IComponent;

private:
    static IComponentSystem<T>* instance;
    uint32_t id = 0;

    virtual void dataInit(T* data){}
    virtual void dataUpdate(T* data){}
    virtual void dataDestroy(T* data){}

protected:
    ChunkArray<T> data;

public:
    IComponentSystem(uint32_t chunkSize);
    ~IComponentSystem();

    inline static IComponentSystem<T>* get(){ return instance; }

    void update() override;

    ChunkArrayIndex addComponent(Actor* owner) override;
    void removeComponent(const ChunkArrayIndex& index) override;
    IComponent* getComponent(const ChunkArrayIndex& index) override;
};

template<class T>
IComponentSystem<T>* IComponentSystem<T>::instance = nullptr;

template<class T>
IComponentSystem<T>::IComponentSystem(uint32_t chunkSize) : data(chunkSize)
{
    instance = this;
}

template<class T>
IComponentSystem<T>::~IComponentSystem()
{
    for(auto& component: data)
    {
        dataDestroy(&component);
    }

    data.clear();
}

template<class T>
void IComponentSystem<T>::update()
{
    for(auto& component: data)
    {
        dataUpdate(&component);
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