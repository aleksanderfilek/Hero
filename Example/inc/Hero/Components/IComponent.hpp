#pragma once 

#include<vector>
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
    virtual uint32_t addComponent(Actor* owner) = 0;
    virtual void removeComponent(uint32_t index) = 0;
    virtual IComponent* getComponent(uint32_t index) = 0;
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
    std::vector<std::pair<bool, T>> data;
    uint32_t usedNumber = 0;
    uint32_t firstEmpty = 0;

public:
    IComponentSystem()
    {
        instance = this;
    }

    ~IComponentSystem()
    {
        for(auto component: data)
        {
            dataDestroy(&component.second);
        }

        data.clear();
    }

    inline static IComponentSystem<T>* get(){ return instance; }

    void update() override
    {
        for(auto component: data)
        {
            if(!component.first)
                continue;

            dataUpdate(&component.second);
        }
    } 

    uint32_t addComponent(Actor* owner) override
    {
        uint32_t index = firstEmpty;

        T t{};
        t.actor = owner;
        std::pair<bool, T> element(true, t);

        if(data.size() <= index)
        {
            data.push_back(element); 
            firstEmpty++;
        }
        else
        {
            data.at(index) = element;
            // prepare for next addition, find first available index
            for(int i = firstEmpty; i < data.size(); i++)
            {
                if(data[i].first == false)
                {
                    firstEmpty = i;
                    break;
                }
            }
        }

        usedNumber++;
        dataInit(&data[index].second);

        return index;
    }

    void removeComponent(uint32_t index) override
    {
        data[index].first = false;
        dataDestroy(&data[index].second);
        usedNumber--;
        
        if(index < firstEmpty)
        {
            firstEmpty = index;
        }
    }

    IComponent* getComponent(uint32_t index) override
    {
        return &data[index].second;
    }
};

template<class T>
IComponentSystem<T>* IComponentSystem<T>::instance = nullptr;

}