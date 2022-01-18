#include"Mesh.hpp"
#include<ThirdParty.hpp>
#include<Debug.hpp>

namespace Hero
{

template<typename T>
MeshBuffer<T>::~MeshBuffer()
{
    delete array;
    length = 0;
}

Mesh::Mesh(const std::string& _name, const std::vector<MeshBuffer<float>>& _buffers,
    const MeshBuffer<int>& _indices)
    : name(_name), buffers(_buffers), indices(_indices)
{

    int buffSize = 0;
    for(auto& buff: buffers)
    {
        buffSize += buff.length;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
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

Mesh::~Mesh()
{

}

void Mesh::draw()
{
    glBindVertexArray(VAO);
    glCheckError();
    glDrawElements(GL_TRIANGLES, indices.length, GL_UNSIGNED_INT, 0);
    glCheckError();
    glBindVertexArray(0);
    glCheckError();
}

} // namespace Hero