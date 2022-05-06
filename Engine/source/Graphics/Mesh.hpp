#pragma once

#include"../Core/IResource.hpp"

#include<cstdint>
#include<string>
#include<vector>
#include<iostream>

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

class Mesh : public IResource
{
private:
    uint32_t VAO, VBO, EBO;
    std::string name;
    std::vector<MeshBuffer<float>> buffers;
    MeshBuffer<int> indices;

public:
    HERO Mesh();
    HERO Mesh(const std::string& _name, const std::vector<MeshBuffer<float>>& _buffers,
        const MeshBuffer<int>& _indices);

    HERO static IResource* Load(const std::string& path);
    HERO static void Unload(IResource* resource);
    static int GetId(){ return 2; }

    HERO void draw();
    HERO void generate();
};

} // namespace Hero
