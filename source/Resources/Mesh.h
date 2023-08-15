// #pragma once

// #include "../Defaults.h"
// #include "ResourceSubsystem.h"
// #include<cstdint>
// #include<string>
// #include<vector>

// enum class BufferType : uint8_t
// {
//     single = 1,
//     vec2 = 2,
//     vec3 = 3
// };

// template<typename T>
// struct MeshBuffer
// {
//     BufferType type = BufferType::single;
//     T* array = nullptr;
//     uint32_t length = 0;

//     void clear()
//     {
//         delete[] array;
//         array = nullptr;
//         length = 0;
//     }
// };

// class HERO_API Mesh : public ResourceHandle
// {
// protected:
//     uint32_t mVAO, mVBO, mEBO;
//     std::vector<MeshBuffer<float>> mBuffers;
//     MeshBuffer<int> mIndices;

// public:
//     Mesh();
//     Mesh(const std::vector<MeshBuffer<float>>& buffers,
//         const MeshBuffer<int>& indices);
//     ~Mesh();

//     static ResourceHandle* load(const uint8_t* Data, ResourceSubsystem* subsystem);
//     static void unload(ResourceHandle* resource);
//     static int getId() { return MESH_ID; }

//     virtual void draw();
//     void generate();
// };