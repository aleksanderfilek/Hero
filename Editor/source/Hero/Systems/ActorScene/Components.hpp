#pragma once

#include<vector>
#include<unordered_map>
#include"../../Core/Sid.hpp"

namespace Hero
{

struct Component
{

};

struct ComponentChunk
{
    bool* Status;
    std::vector<Component*> Components;
};

class ComponentsPool
{
private:
    uint32_t PoolSize = 1;

    std::unordered_map<Sid, uint32_t, SidHashFunction> ComponentsMap;
    std::vector<ComponentChunk> Chunks;

public:
    HERO ComponentsPool(uint32_t NewPoolSize = 1, uint32_t ChunkCount = 1);
    HERO ~ComponentsPool();

    template<typename T> bool RegisterComponent(const Sid& Id)
    {
        if(ComponentsMap.find(Id) != ComponentsMap.end())
        {
            return false;
        }

        std::pair<Sid, uint32_t> data(Id, Chunks[0].Components.size());
        ComponentsMap.insert(data);

        for(ComponentChunk& chunk: Chunks)
        {
            chunk.Components.push_back(new T[PoolSize]);
        }

        return true;
    }



};

}