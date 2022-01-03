#include"IComponent.hpp"

namespace Hero
{
template<typename T>
IComponentSystem<T>::IComponentSystem(uint32_t _startSize = 1, 
    uint32_t _chunkSize = 1)
{
    data.reserve(_startSize);
    chunkSize = _chunkSize;
}

template<typename T>
IComponentSystem<T>::~IComponentSystem()
{
    for(auto component: data)
    {
        close(&component.second);
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

        update(&component.second);
    }
} 

template<typename T>
IComponent* IComponentSystem<T>::add(const T& data)
{
    uint32_t index = firstEmpty;
    std::pair<bool, T> element(true, data);
    
    element.second.index = this;
    element.second.index = index;
    data[firstEmpty] = element;
    usedNumber++;
    dataInit(&data.at(index).second);

    if(data.size() =< usedNumber)
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
void IComponentSystem<T>::remove(IComponent* data)
{
    data.at(data->index).first = false;
    usedNumber--;
    
    if(data->index < firstEmpty)
    {
        firstEmpty = data->index;
    }
}

}