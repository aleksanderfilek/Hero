#include"Mesh.hpp"
#include<ThirdParty.hpp>
#include<Debug.hpp>

#include<iostream>
#include<fstream>

namespace Hero
{

HERO Mesh::Mesh()
{
    id = GetId(); 
}

HERO Mesh::Mesh(const std::string& _name, const std::vector<MeshBuffer<float>>& _buffers,
    const MeshBuffer<int>& _indices)
    : name(_name), buffers(_buffers), indices(_indices)
{
    generate();
}

HERO IResource* Mesh::Load(const std::string& path)
{
    std::vector<MeshBuffer<float>> buffers;
    MeshBuffer<int> indices;

    std::ifstream input(path, std::ios::binary);

    uint32_t nameSize;
    input.read((char*)&nameSize, sizeof(uint32_t));
    char nameArr[nameSize];
    input.read(nameArr, nameSize * sizeof(char));
    
    uint32_t indicesCount;
    input.read((char*)&indicesCount, sizeof(uint32_t));
    int* indicesArr = new int[indicesCount];
    input.read((char*)indicesArr, indicesCount * sizeof(int));
    indices.length = indicesCount;
    indices.array = indicesArr;

    uint32_t bufferCount;
    input.read((char*)&bufferCount, sizeof(uint32_t));

    for(int i = 0; i < bufferCount; i++)
    {
        uint8_t bufferType;
        input.read((char*)&bufferType, sizeof(uint8_t));
        uint32_t bufferLength;
        input.read((char*)&bufferLength, sizeof(uint32_t));
        float* bufferArr = new float[bufferLength];
        input.read((char*)bufferArr, bufferLength * sizeof(float));

        buffers.push_back((MeshBuffer<float>){(BufferType)bufferType, bufferArr, bufferLength});
    }

    input.close();

    Mesh* mesh = new Mesh(path, buffers, indices);
    return mesh;
}

HERO void Mesh::Unload(IResource* resource)
{
    Mesh* mesh = (Mesh*)resource;
    mesh->indices.clear();
    for(auto buff: mesh->buffers)
    {
        buff.clear();
    }

    glDeleteBuffers(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
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
