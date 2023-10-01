#include "Mesh.h"
#include"../ThirdParty/GL/Gl.h"

#include <iostream>

Mesh::Mesh(const Array<MeshBuffer<float>>& Buffers,
    const MeshBuffer<int>& Indices)
    : buffers(Buffers), indices(Indices)
{
    Generate();
}

Mesh::~Mesh()
{
    indices.Clear();
    for (auto buff : buffers)
    {
        buff.Clear();
    }

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Mesh::Draw()
{
    glBindVertexArray(vao);
    GlCheckError();
    glDrawElements(GL_TRIANGLES, indices.Length, GL_UNSIGNED_INT, 0);
    GlCheckError();
    glBindVertexArray(0);
    GlCheckError();
}

void Mesh::Generate()
{
    int buffSize = 0;
    for (auto& buff : buffers)
    {
        buffSize += buff.Length;
    }

    glGenVertexArrays(1, &vao);
    GlCheckError();
    glGenBuffers(1, &vbo);
    GlCheckError();
    glGenBuffers(1, &ebo);
    GlCheckError();
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffSize * sizeof(float), NULL, GL_STATIC_DRAW);
    GlCheckError();
    size_t buffOffset = 0;

    for (auto& buff : buffers)
    {
        uint32_t size = buff.Length * sizeof(float);
        if (size == 0)
        {
            std::cout << "Buffer with lenght zero!" << std::endl;
        }

        glBufferSubData(GL_ARRAY_BUFFER, buffOffset, size, buff.Array);
        GlCheckError();
        buffOffset += size;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Length * sizeof(uint32_t), indices.Array, GL_STATIC_DRAW);
    GlCheckError();

    buffOffset = 0;
    for (int i = 0; i < buffers.Length(); i++)
    {
        const MeshBuffer<float>& buff = buffers[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, (uint32_t)buff.Type, GL_FLOAT, GL_FALSE, (uint32_t)buff.Type * sizeof(float), (void*)(buffOffset));
        GlCheckError();
        buffOffset += buff.Length * sizeof(float);
    }
    glBindVertexArray(0);
}