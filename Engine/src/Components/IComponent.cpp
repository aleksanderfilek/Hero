#include"IComponent.hpp"

namespace Hero
{
template<typename T>
IComponentSystem<T>::IComponentSystem(uint32_t _startSize , uint32_t _chunkSize)
{
    data.reserve(_startSize);
    chunkSize = _chunkSize;
}

template<typename T>
IComponentSystem<T>::~IComponentSystem()
{
    for(auto component: data)
    {
        dataClose(&component.second);
    }

    data.clear();
}

template<typename T>
void IComponentSystem<T>::update()
{
    for(auto component: data)
    {
        if(!component.first)
            continue;

        dataUpdate(&component.second);
    }
} 

template<typename T>
IComponent* IComponentSystem<T>::add(const T& component)
{
    uint32_t index = firstEmpty;
    std::pair<bool, T> element(true, component);
    
    element.second.index = this;
    element.second.index = index;
    data[firstEmpty] = element;
    usedNumber++;
    dataInit(&data.at(index).second);

    if(data.size() <= usedNumber)
    {
        data.resize(usedNumber + chunkSize);
    }

    for(int i = firstEmpty; i < data.size(); i++)
    {
        if(data.at(i).first == false)
        {
            firstEmpty = i;
            break;
        }
    }

    return &data.at(index).second;
}

template<typename T>
void IComponentSystem<T>::remove(IComponent* component)
{
    data.at(component->index).first = false;
    usedNumber--;
    
    if(component->index < firstEmpty)
    {
        firstEmpty = component->index;
    }
}

}