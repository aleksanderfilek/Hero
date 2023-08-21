#pragma once

// #include "../Defaults.h"
// #include "ResourceSubsystem.h"
// #include<cstdint>
// #include<string>
// #include<vector>

#include "../Definitions.h"
#include "ResourceHandle.h"
#include "../Containers/Array.h"
#include <cstdint>

enum class BufferType
{
    SINGLE =    1,
    VEC2 =      2,
    VEC3 =      3
};

template<typename T>
struct MeshBuffer
{
    BufferType Type = BufferType::SINGLE;
    T* Array = nullptr;
    int Length = 0;

    void Clear()
    {
        delete[] Array;
        Array = nullptr;
        Length = 0;
    }
};

class HERO_API Mesh : public ResourceHandle
{
protected:
    uint32_t vao, vbo, ebo;
    Array<MeshBuffer<float>> buffers;
    MeshBuffer<int> indices;

    void Generate();

public:
    Mesh(const Array<MeshBuffer<float>>& Buffers,
        const MeshBuffer<int>& Indices);
    ~Mesh();

    virtual void Draw();
};