#pragma once 

#include<vector>
#include<cstdint>
#include<utility>

namespace Hero
{

class Actor;
class IComponentSystemHandler;

struct IComponent
{
    uint32_t index = 0;
    Actor* actor = nullptr;
};


class IComponentSystemHandle
{
public:
    virtual IComponent* addComponent(Actor* owner) = 0;
    virtual void removeComponent(IComponent* component) = 0;
    virtual void update() = 0;
};

template<class T>
class HERO IComponentSystem : public IComponentSystemHandle
{
    friend struct IComponent;

private:
    static IComponentSystem<T>* instance;

    int startSize;
    int chunkSize;
    virtual void dataInit(T* data){}
    virtual void dataUpdate(T* data){}
    virtual void dataDestroy(T* data){}

protected:
    std::vector<std::pair<bool, T>> data;
    uint32_t usedNumber = 0;
    uint32_t firstEmpty = 0;

public:
    IComponentSystem(uint32_t _startSize, uint32_t _chunkSize)
    {
        instance = this;

        data.reserve(_startSize);
        chunkSize = _chunkSize;
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

    IComponent* addComponent(Actor* owner) override
    {
        uint32_t index = firstEmpty;
        std::pair<bool, T> element;
        element.first = true;

        element.second.index = index;
        element.second.actor = owner;

        if(data.size() < index)
        {
           data.push_back(element); 
        }
        else
        {
            data[index] = element;
        }

        usedNumber++;
        dataInit(&data[index].second);

        // resize component vector by size
        if(data.size() <= usedNumber)
        {
            data.resize(usedNumber + chunkSize);
        }

        // prepare for next addition, find first available index
        for(int i = firstEmpty; i < data.size(); i++)
        {
            if(data[i].first == false)
            {
                firstEmpty = i;
                break;
            }
        }

        return &data[index].second;
    }

    void removeComponent(IComponent* component) override
    {
        data[component->index].first = false;
        dataDestroy(&data[component->index].second);
        usedNumber--;
        
        if(component->index < firstEmpty)
        {
            firstEmpty = component->index;
        }
    }
};

template<class T>
IComponentSystem<T>* IComponentSystem<T>::instance = nullptr;

}