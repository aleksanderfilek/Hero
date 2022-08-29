#include"Components.hpp"

namespace Hero
{

HERO ComponentsPool::ComponentsPool(uint32_t NewPoolSize, uint32_t ChunkCount)
    : PoolSize(NewPoolSize)
{
    for(int i = 0; i < ChunkCount; i++)
    {
        ComponentChunk chunk;
        chunk.Status = new bool[PoolSize]{ false };
        Chunks.push_back(chunk);
    }
}

HERO ComponentsPool::~ComponentsPool()
{
    ComponentsMap.clear();

    for(ComponentChunk& chunk: Chunks)
    {
        delete[] chunk.Status;
        for(Component* component: chunk.Components)
        {
            delete[] component;
        }
        chunk.Components.clear();
    }
    Chunks.clear();
}

}