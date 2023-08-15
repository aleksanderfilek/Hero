// #include "Mesh.h"
// #include"../ThirdParty/GL/Gl.h"
// #include"../Core/Debug.h"
// #include"../Utilities/ByteOperations.h"

// #include<iostream>

// Mesh::Mesh()
// {}

// Mesh::Mesh(const std::vector<MeshBuffer<float>>& buffers,
//     const MeshBuffer<int>& indices)
//     : mBuffers(buffers), mIndices(indices)
// {
//     generate();
// }

// ResourceHandle* Mesh::load(const uint8_t* Data, ResourceSubsystem* subsystem)
// {
//     int index = 0;
//     std::vector<MeshBuffer<float>> buffers;
//     MeshBuffer<int> indices;
//     uint32_t indicesCount = readUint32(Data, &index);

//     int* indicesArr = new int[indicesCount];
//     readPtr(Data, &index, (uint8_t*)indicesArr, indicesCount * sizeof(int));
//     indices.length = indicesCount;
//     indices.array = indicesArr;

//     uint32_t bufferCount = readUint32(Data, &index);

//     for (int i = 0; i < bufferCount; i++)
//     {
//         uint8_t bufferType = readUint8(Data, &index);
//         uint32_t bufferLength = readUint32(Data, &index);
//         float* bufferArr = new float[bufferLength / sizeof(float)];
//         readPtr(Data, &index, (uint8_t*)bufferArr, bufferLength);

//         MeshBuffer<float> buffer = { (BufferType)bufferType, bufferArr, bufferLength / sizeof(float) };
//         buffers.push_back(buffer);
//     }

//     Mesh* mesh = new Mesh(buffers, indices);

//     return mesh;
// }

// Mesh::~Mesh()
// {
//     mIndices.clear();
//     for (auto buff : mBuffers)
//     {
//         buff.clear();
//     }

//     glDeleteBuffers(1, &mVAO);
//     glDeleteBuffers(1, &mVBO);
//     glDeleteBuffers(1, &mEBO);
// }

// void Mesh::unload(ResourceHandle* resource)
// {
//     Mesh* mesh = (Mesh*)resource;
//     for (auto buffer : mesh->mBuffers)
//     {
//         delete[] buffer.array;
//     }
//     delete resource;
// }

// void Mesh::draw()
// {
//     glBindVertexArray(mVAO);
//     glCheckError();
//     glDrawElements(GL_TRIANGLES, mIndices.length, GL_UNSIGNED_INT, 0);
//     glCheckError();
//     glBindVertexArray(0);
//     glCheckError();
// }

// void Mesh::generate()
// {
//     int buffSize = 0;
//     for (auto& buff : mBuffers)
//     {
//         buffSize += buff.length;
//     }

//     glCheckError();
//     glGenVertexArrays(1, &mVAO);
//     glCheckError();
//     glGenBuffers(1, &mVBO);
//     glCheckError();
//     glGenBuffers(1, &mEBO);
//     glCheckError();
//     glBindVertexArray(mVAO);

//     glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//     glBufferData(GL_ARRAY_BUFFER, buffSize * sizeof(float), NULL, GL_STATIC_DRAW);
//     glCheckError();
//     size_t buffOffset = 0;

//     for (auto& buff : mBuffers)
//     {
//         uint32_t size = buff.length * sizeof(float);
//         if (size == 0)
//         {
//             std::cout << "Buffer with lenght zero!" << std::endl;
//         }

//         glBufferSubData(GL_ARRAY_BUFFER, buffOffset, size, buff.array);
//         glCheckError();
//         buffOffset += size;
//     }

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.length * sizeof(uint32_t), mIndices.array, GL_STATIC_DRAW);
//     glCheckError();

//     buffOffset = 0;
//     for (int i = 0; i < mBuffers.size(); i++)
//     {
//         MeshBuffer<float>& buff = mBuffers[i];
//         glEnableVertexAttribArray(i);
//         glVertexAttribPointer(i, (uint32_t)buff.type, GL_FLOAT, GL_FALSE, (uint32_t)buff.type * sizeof(float), (void*)(buffOffset));
//         glCheckError();
//         buffOffset += buff.length * sizeof(float);
//     }
//     glBindVertexArray(0);
// }