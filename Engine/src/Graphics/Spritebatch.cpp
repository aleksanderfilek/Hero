#include"Spritebatch.hpp"
#include"Texture.hpp"
#include"Shader.hpp"
#include"ThirdParty.hpp"

namespace Hero
{

HERO Spritebatch::Spritebatch(uint32_t capacity, uint32_t maxTextures)
{
    spriteCapacity = capacity;
    quadBuffer = new SpritebatchVertex[4 * capacity];
    quadBufferPtr = quadBuffer;
    
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * capacity * sizeof(SpritebatchVertex), NULL, GL_DYNAMIC_DRAW);  

    glEnableVertexArrayAttrib(VAO, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)0);

    glEnableVertexArrayAttrib(VAO, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)(sizeof(Float3)));

    glEnableVertexArrayAttrib(VAO, 2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)(sizeof(Float3) + sizeof(Float2)));

    glEnableVertexArrayAttrib(VAO, 3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(SpritebatchVertex), (const void*)(sizeof(Float3) + sizeof(Float2) + sizeof(float)));

    indexCount = 0;
    maxIndexCount = 6 * capacity;
    uint32_t indices[maxIndexCount];
    uint32_t offset = 0;
    for(int i = 0; i < maxIndexCount; i+=6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    glCreateBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    maxTextureSlots = maxTextures;
    textureSlots = new const Texture*[maxTextures]{nullptr};
    textureSlotIndex = 0;

    sampler = new int[maxTextures];
    for(int i = 0; i < maxTextures; i++)
    {
        sampler[i] = i;
    }
}

HERO Spritebatch::~Spritebatch()
{
  delete[] textureSlots;

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  delete[] quadBuffer;
  delete[] sampler;
}

HERO void Spritebatch::begin()
{
    glUniform1iv(shaderTexturesLocation, maxTextureSlots, sampler);

    quadBufferPtr = quadBuffer;
}

HERO void Spritebatch::end()
{
    GLsizeiptr size = (uint8_t*)quadBufferPtr - (uint8_t*)quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, quadBuffer);

    for(int i = 0; i < textureSlotIndex; i++)
    {
        glBindTextureUnit(i, textureSlots[i]->getGlId());
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
    indexCount = 0;
    textureSlotIndex = 0;
}
#include<iostream>
HERO void Spritebatch::drawTexture(const Texture* texture, const Int2& position, const Int2& size, Float4 rect)
{
    if(indexCount >= maxIndexCount || 
        textureSlotIndex > maxTextureSlots)
    {
        end();
        begin();
    }

    float textureIndex = -1.0f;
    // check registred texture
    for(int i = 0; i <= textureIndex; i++)
    {
        if(textureSlots[i]->getGlId() == texture->getGlId())
        {
            textureIndex = (float)i;
            break;
        }
    }

    // // add texture if not registered
    if(textureIndex == -1.0f)
    {
        textureIndex = textureSlotIndex;
        textureSlots[textureSlotIndex] = texture;
        textureSlotIndex++;
    }

    quadBufferPtr->position = (Float3){ (float)position.x, (float)position.y, 0.0f };
    quadBufferPtr->texCoords = (Float2){ rect.x, rect.y };
    quadBufferPtr->texIndex = textureIndex;
    quadBufferPtr->color = (Float4){ 1.0f, 1.0f, 1.0f, 1.0f };
    quadBufferPtr++;

    quadBufferPtr->position = (Float3){ (float)(position.x + size.x), (float)position.y, 0.0f };
    quadBufferPtr->texCoords = (Float2){ rect.z, rect.y };
    quadBufferPtr->texIndex = textureIndex;
    quadBufferPtr->color = (Float4){ 1.0f, 1.0f, 1.0f, 1.0f };
    quadBufferPtr++;

    quadBufferPtr->position = (Float3){ (float)(position.x + size.x), (float)(position.y + size.y), 0.0f };
    quadBufferPtr->texCoords = (Float2){ rect.z, rect.w };
    quadBufferPtr->texIndex = textureIndex;
    quadBufferPtr->color = (Float4){ 1.0f, 1.0f, 1.0f, 1.0f };
    quadBufferPtr++;

    quadBufferPtr->position = (Float3){ (float)position.x, (float)(position.y + size.y), 0.0f };
    quadBufferPtr->texCoords = (Float2){ rect.x, rect.w };
    quadBufferPtr->texIndex = textureIndex;
    quadBufferPtr->color = (Float4){ 1.0f, 1.0f, 1.0f, 1.0f };
    quadBufferPtr++;

    indexCount += 6;
}

HERO void Spritebatch::setShader(Shader* _shader)
{
    shaderTexturesLocation = _shader->getUniformLocation("sb_textures");
}

}