#include "MultiTextureSpritebatch.h"
#include "../Resources/Texture.h"
#include "../Resources/Shader.h"
#include "../ThirdParty/GL/Gl.h"
#include "../GenericTypes/StringId.h"
#include <iostream>


MultiTextureSpritebatch::MultiTextureSpritebatch(uint32_t Capacity, uint32_t MaxTextures)
{
    spriteCapacity = Capacity;
    quadBuffer = new MultiTextureSpritebatchVertex[4 * spriteCapacity];
    quadBufferPtr = quadBuffer;
    
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * spriteCapacity * sizeof(MultiTextureSpritebatchVertex), NULL, GL_DYNAMIC_DRAW);  

    glEnableVertexArrayAttrib(vao, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MultiTextureSpritebatchVertex), 
        (const void*)0);

    glEnableVertexArrayAttrib(vao, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MultiTextureSpritebatchVertex), 
        (const void*)(sizeof(Float3)));

    glEnableVertexArrayAttrib(vao, 2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(MultiTextureSpritebatchVertex), 
        (const void*)(sizeof(Float3) + sizeof(Float2)));

    glEnableVertexArrayAttrib(vao, 3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MultiTextureSpritebatchVertex), 
        (const void*)(sizeof(Float3) + sizeof(Float2) + sizeof(float)));

    glEnableVertexArrayAttrib(vao, 3);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(MultiTextureSpritebatchVertex), 
        (const void*)(sizeof(Float3) + sizeof(Float2) + sizeof(float) + sizeof(Color)));


    indexCount = 0;
    maxIndexCount = 6 * spriteCapacity;
    indices = new uint32_t[maxIndexCount];
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

    glCreateBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndexCount * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW);

    maxTextureSlots = MaxTextures;
    textureSlots = new const Texture*[maxTextureSlots]{nullptr};
    textureSlotIndex = 0;

    sampler = new int[maxTextureSlots];
    for(int i = 0; i < maxTextureSlots; i++)
    {
        sampler[i] = i;
    }
}

MultiTextureSpritebatch::~MultiTextureSpritebatch()
{
    delete[] textureSlots;

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    delete[] quadBuffer;
    delete[] sampler;
    delete[] indices;
}

void MultiTextureSpritebatch::Begin()
{
    glUniform1iv(shaderTexturesLocation, maxTextureSlots, sampler);

    quadBufferPtr = quadBuffer;

    indexCount = 0;
    textureSlotIndex = 0;
}

void MultiTextureSpritebatch::End()
{
    GLsizeiptr size = (uint8_t*)quadBufferPtr - (uint8_t*)quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, quadBuffer);
    for(int i = 0; i < textureSlotIndex; i++)
    {
        glBindTextureUnit(i, textureSlots[i]->GetGlId());
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
}

void MultiTextureSpritebatch::DrawTexture(const Texture* Texture, const Int2& Position, const Int2& Size, Float4 Rect, const Color& Color)
{
    return;
    if(indexCount >= maxIndexCount || textureSlotIndex >= maxTextureSlots)
    {
        End();
        Begin();
    }

    float textureIndex = -1.0f;
    // check registred texture
    for(int i = 0; i < textureSlotIndex; i++)
    {
        if(textureSlots[i]->GetGlId() == Texture->GetGlId())
        {
            textureIndex = (float)i;
            break;
        }
    }

    // add texture if not registered
    if(textureIndex == -1.0f)
    {
        textureIndex = textureSlotIndex;
        textureSlots[textureSlotIndex] = Texture;
        textureSlotIndex++;
    }

    quadBufferPtr->Position = { (float)Position.X, (float)Position.Y, 0.0f };
    quadBufferPtr->TexCoords = { Rect.X, Rect.Y };
    quadBufferPtr->TexIndex = textureIndex;
    quadBufferPtr->Color = Color;
    quadBufferPtr++;

    quadBufferPtr->Position = { (float)(Position.X + Size.X), (float)Position.Y, 0.0f };
    quadBufferPtr->TexCoords = { Rect.Z, Rect.Y };
    quadBufferPtr->TexIndex = textureIndex;
    quadBufferPtr->Color = Color;
    quadBufferPtr++;

    quadBufferPtr->Position = { (float)(Position.X + Size.X), (float)(Position.Y + Size.Y), 0.0f };
    quadBufferPtr->TexCoords = { Rect.Z, Rect.W };
    quadBufferPtr->TexIndex = textureIndex;
    quadBufferPtr->Color = Color;
    quadBufferPtr++;

    quadBufferPtr->Position = { (float)Position.X, (float)(Position.Y + Size.Y), 0.0f };
    quadBufferPtr->TexCoords = { Rect.X, Rect.W };
    quadBufferPtr->TexIndex = textureIndex;
    quadBufferPtr->Color = Color;
    quadBufferPtr++;

    indexCount += 6;
}

void MultiTextureSpritebatch::SetShader(Shader* Shader)
{
    Shader->Bind();
    shaderTexturesLocation = Shader->GetUniformLocation(StringId("sb_textures"));
}