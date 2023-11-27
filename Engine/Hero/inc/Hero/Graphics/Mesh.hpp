#pragma once

#include"../Systems/Resources.hpp"
#include"../Core/Sid.hpp"
#include<cstdint>
#include<string>
#include<vector>
#include<iostream>

/*
file format
resourceId
indicesCount
indicesArray
bufferCount
bufferType
bufferLength
bufferArray
...
*/

namespace Hero
{

enum class BufferType : uint8_t
{
    single = 1,
    vec2 = 2,
    vec3 = 3
};

template<typename T>
struct MeshBuffer
{
    BufferType type = BufferType::single;
    T* array = nullptr;
    uint32_t length = 0;

    void clear()
    {
        delete[] array;
        array = nullptr;
        length = 0;
    }
};

class Mesh : public ResourceHandle
{
protected:
    uint32_t VAO, VBO, EBO;
    std::vector<MeshBuffer<float>> buffers;
    MeshBuffer<int> indices;

public:
    HERO Mesh();
    HERO Mesh(const std::vector<MeshBuffer<float>>& _buffers,
        const MeshBuffer<int>& _indices);
    HERO ~Mesh();

    HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
    HERO static void Unload(ResourceHandle* resource);
    static int GetId(){ return MESH_ID; }

    HERO virtual void draw();
    HERO void generate();
};

} // namespace Hero
