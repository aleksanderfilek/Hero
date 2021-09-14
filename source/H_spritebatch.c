#include<stdint.h>
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include"H_texture.h"
#include"H_shader.h"
#include"H_math.h"

typedef struct
{
    HeroFloat3 position;
    HeroFloat2 texCoords;
    float texIndex;
} _HeroVertex;

typedef struct
{
    uint32_t spriteCapacity;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    _HeroVertex* quadBuffer;
    _HeroVertex* quadBufferPtr;

    uint32_t indexCount;
    uint32_t maxIndexCount;

    uint32_t maxTextureSlots;
    HeroTexture** textureSlots;
    uint32_t textureSlotIndex;

    const HeroShader* shader;
    uint32_t shaderTexturesLocation;
} HeroSpriteBatch;


HeroSpriteBatch* heroSpriteBatchInit(uint32_t capacity, uint32_t maxTextures, const HeroShader* shader)
{
    HeroSpriteBatch* spriteBatch = (HeroSpriteBatch*)malloc(sizeof(HeroSpriteBatch));
    spriteBatch->spriteCapacity = capacity;
    spriteBatch->quadBuffer = (_HeroVertex*)malloc(4 * capacity * sizeof(_HeroVertex));
    spriteBatch->quadBufferPtr = spriteBatch->quadBuffer;

    glCreateVertexArrays(1, &spriteBatch->VAO);
    glBindVertexArray(spriteBatch->VAO);

    glCreateBuffers(1, &spriteBatch->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, spriteBatch->VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * capacity * sizeof(_HeroVertex), NULL, GL_DYNAMIC_DRAW);  
    
    glEnableVertexArrayAttrib(spriteBatch->VAO, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(_HeroVertex), (const void*)0);

    glEnableVertexArrayAttrib(spriteBatch->VAO, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(_HeroVertex), (const void*)(sizeof(HeroFloat3)));

    glEnableVertexArrayAttrib(spriteBatch->VAO, 2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(_HeroVertex), (const void*)(sizeof(HeroFloat3) + sizeof(HeroFloat2)));

    spriteBatch->indexCount = 0;
    spriteBatch->maxIndexCount = 6 * capacity;
    uint32_t indices[spriteBatch->maxIndexCount];
    uint32_t offset = 0;
    for(int i = 0; i < spriteBatch->maxIndexCount; i+=6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    glCreateBuffers(1, &spriteBatch->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteBatch->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    spriteBatch->maxTextureSlots = maxTextures;
    spriteBatch->textureSlots = (HeroTexture**)malloc(maxTextures * sizeof(HeroTexture*));
    memset(spriteBatch->textureSlots, 0, maxTextures * sizeof(HeroTexture*));
    spriteBatch->textureSlotIndex = 0;

    spriteBatch->shader = shader;
    heroShaderBind(shader);
    spriteBatch->shaderTexturesLocation = heroShaderGetUniformLocation(shader, "sb_textures");
    uint32_t viewLoc = heroShaderGetUniformLocation(shader, "view");
    HeroMat4x4 view = heroMathOrthographicMatrix(640, 480, 0.00f, 100.0f);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)(&(view.col[0])));

    int sampler[maxTextures];
    for(int i = 0; i < maxTextures; i++)
    {
        sampler[i] = i;
    }
    glUniform1iv(spriteBatch->shaderTexturesLocation, maxTextures, sampler);

    return spriteBatch;
}

void heroSpriteBatchDestroy(HeroSpriteBatch* spriteBatch)
{
    free(spriteBatch->textureSlots);

    glDeleteVertexArrays(1, &spriteBatch->VAO);
    glDeleteBuffers(1, &spriteBatch->VBO);
    glDeleteBuffers(1, &spriteBatch->EBO);

    free(spriteBatch->quadBuffer);
}

void heroSpriteBatchBegin(HeroSpriteBatch* spriteBatch)
{
    spriteBatch->quadBufferPtr = spriteBatch->quadBuffer;
}

void heroSpriteBatchEnd(HeroSpriteBatch* spriteBatch)
{
    GLsizeiptr size = (uint8_t*)spriteBatch->quadBufferPtr - (uint8_t*)spriteBatch->quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, spriteBatch->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, spriteBatch->quadBuffer);

    heroShaderBind(spriteBatch->shader);

    for(int i = 0; i < spriteBatch->textureSlotIndex; i++)
    {
        glBindTextureUnit(i, heroTextureGetGlID(spriteBatch->textureSlots[i]));
    }

    glBindVertexArray(spriteBatch->VAO);
    glDrawElements(GL_TRIANGLES, spriteBatch->indexCount, GL_UNSIGNED_INT, NULL);
    spriteBatch->indexCount = 0;
    spriteBatch->textureSlotIndex = 0;
}

void heroSpriteBatchDrawTexture(HeroSpriteBatch* spriteBatch, const HeroTexture* texture, const HeroInt2 position, const HeroInt2 size)
{
    if(spriteBatch->indexCount >= spriteBatch->maxIndexCount || 
        spriteBatch->textureSlotIndex > spriteBatch->maxTextureSlots)
    {
        heroSpriteBatchEnd(spriteBatch);
        heroSpriteBatchBegin(spriteBatch);
    }

    float textureIndex = 0.0f;
    // check registred texture
    for(int i = 1; i < spriteBatch->maxTextureSlots; i++)
    {
        if(spriteBatch->textureSlots[i] == texture)
        {
            textureIndex = (float)i;
            break;
        }
    }

    // // add texture if not registered
    if(textureIndex == 0.0f)
    {
        textureIndex = spriteBatch->textureSlotIndex;
        spriteBatch->textureSlots[spriteBatch->textureSlotIndex] = (HeroTexture*)texture;
        spriteBatch->textureSlotIndex++;
    }

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)position.x, (float)position.y, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 0.0f, 0.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr++;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)(position.x + size.x), (float)position.y, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 1.0f, 0.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr++;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)(position.x + size.x), (float)(position.y + size.y), 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 1.0f, 1.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr++;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)position.x, (float)(position.y + size.y), 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 0.0f, 1.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr++;

    spriteBatch->indexCount += 6;
}
