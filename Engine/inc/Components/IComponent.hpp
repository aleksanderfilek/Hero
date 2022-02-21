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

    virtual void dataInit(T* data){}
    virtual void dataUpdate(T* data){}
    virtual void dataDestroy(T* data){}

protected:
    ChunkArray<T> data;

public:
    IComponentSystem(uint32_t chunkSize) : data(chunkSize)
    {
        instance = this;
        data = new ChunkArray<T>(chunkSize);
    }

    ~IComponentSystem()
    {
        // for(auto component: data)
        // {
        //     dataDestroy(&component.second);
        // }

        // data.clear();
    }

    inline static IComponentSystem<T>* get(){ return instance; }

    void update() override
    {
        // for(auto component: data)
        // {
        //     if(!component.first)
        //         continue;

        //     dataUpdate(&component.second);
        // }
    } 

    ChunkArrayIndex addComponent(Actor* owner) override
    {
        T t{};
        t.actor = owner;
        dataInit(&t);
        return data.add(t);
    }

    void removeComponent(const ChunkArrayIndex& index) override
    {
        dataDestroy(&(data[index]));
        data.remove(index);
    }

    IComponent* getComponent(const ChunkArrayIndex& index) override
    {
        return &(data[index]);
    }
};

template<class T>
IComponentSystem<T>* IComponentSystem<T>::instance = nullptr;

}