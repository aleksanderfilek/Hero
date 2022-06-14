#include"Mesh.hpp"
#include"../ThirdParty/GL/Gl.hpp"
#include"../Core/Debug.hpp"
#include"../Utility/ByteOperations.hpp"

#include<iostream>

namespace Hero
{

HERO Mesh::Mesh()
{}

HERO Mesh::Mesh(const std::vector<MeshBuffer<float>>& _buffers,
    const MeshBuffer<int>& _indices)
    : buffers(_buffers), indices(_indices)
{
    generate();
}

HERO ResourceHandle* Mesh::Load(uint8_t* Data, Resources* system)
{
    int index = 0;
    
    std::vector<MeshBuffer<float>> buffers;
    MeshBuffer<int> indices;
    
    uint32_t indicesCount = ReadUint32(Data, &index);
    int* indicesArr = new int[indicesCount];
    ReadPtr(Data, &index, indicesArr, indicesCount);
    indices.length = indicesCount;
    indices.array = indicesArr;

    uint32_t bufferCount = ReadUint32(Data, &index);

    for(int i = 0; i < bufferCount; i++)
    {
        uint8_t bufferType = ReadUint8(Data, &index);
        uint32_t bufferLength = ReadUint32(Data, &index);
        float* bufferArr = new float[bufferLength];
        ReadPtr(Data, &index, indicesArr, indicesCount);

        buffers.push_back((MeshBuffer<float>){(BufferType)bufferType, bufferArr, bufferLength});
    }

    Mesh* mesh = new Mesh(buffers, indices);
    return mesh;
}

HERO Mesh::~Mesh()
{
    indices.clear();
    for(auto buff: buffers)
    {
        buff.clear();
    }

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

HERO void Mesh::Unload(ResourceHandle* resource)
{
    delete resource;
}

HERO void Mesh::draw()
{
    glBindVertexArray(VAO);
    glCheckError();
    glDrawElements(GL_TRIANGLES, indices.length, GL_UNSIGNED_INT, 0);
    glCheckError();
    glBindVertexArray(0);
    glCheckError();
}

HERO void Mesh::generate()
{
    int buffSize = 0;
    for(auto& buff: buffers)
    {
        buffSize += buff.length;
    }
    glCheckError();
    glGenVertexArrays(1, &VAO);
    glCheckError();
    glGenBuffers(1, &VBO);
    glCheckError();
    glGenBuffers(1, &EBO);
    glCheckError();
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, buffSize * sizeof(float), NULL, GL_STATIC_DRAW);  
    glCheckError();
    size_t buffOffset = 0;

    for(auto& buff: buffers)
    {
        uint32_t size = buff.length * sizeof(float);
        if(size == 0) std::cout<<"Buffer with lenght zero!"<<std::endl;
        glBufferSubData(GL_ARRAY_BUFFER, buffOffset, size, buff.array);
        glCheckError();
        buffOffset += size;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.length * sizeof(uint32_t), indices.array, GL_STATIC_DRAW);
    glCheckError();

    buffOffset = 0;
    for(int i = 0; i < buffers.size(); i++)
    {
        MeshBuffer<float>& buff = buffers[i];
        glEnableVertexAttribArray(i);	
        glVertexAttribPointer(i, (uint32_t)buff.type, GL_FLOAT, GL_FALSE, (uint32_t)buff.type * sizeof(float), (void*)(buffOffset));
        glCheckError();
        buffOffset += buff.length * sizeof(float);
    }
    glBindVertexArray(0);
}

} // namespace Hero
