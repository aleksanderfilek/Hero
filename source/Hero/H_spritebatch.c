#include<stdint.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#include"Hero/H_headers.h"
#include"Hero/H_texture.h"
#include"Hero/H_shader.h"
#include"Hero/H_math.h"
#include"Hero/H_color.h"
#include"Hero/H_window.h"
#include"Hero/H_debug.h"

typedef struct
{
    HeroFloat3 position;
    HeroFloat2 texCoords;
    float texIndex;
    HeroFloat4 color;
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

    uint32_t viewLoc;
    HeroMatrix4x4 viewMatrix;
    int *sampler;
} HeroSpriteBatch;


HeroSpriteBatch* heroSpriteBatchInit(HeroWindow* window, uint32_t capacity, uint32_t maxTextures, const HeroShader* shader)
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

    glEnableVertexArrayAttrib(spriteBatch->VAO, 3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(_HeroVertex), (const void*)(sizeof(HeroFloat3) + sizeof(HeroFloat2) + sizeof(float)));

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
    spriteBatch->viewLoc = heroShaderGetUniformLocation(shader, "view");

    HeroInt2 windowSize = heroWindowGetSize(window);

    spriteBatch->viewMatrix = heroMathPixelScreenMatrix(windowSize.x, windowSize.y, 0.00f, 100.0f);

    spriteBatch->sampler = (int*)malloc(maxTextures * sizeof(int));
    for(int i = 0; i < maxTextures; i++)
    {
        spriteBatch->sampler[i] = i;
    }

    return spriteBatch;
}
#include<stdio.h>
void heroSpriteBatchDestroy(HeroSpriteBatch* spriteBatch)
{
    printf("ok1\n");
    free(spriteBatch->textureSlots);
    printf("ok2\n");

    glDeleteVertexArrays(1, &spriteBatch->VAO);
    glDeleteBuffers(1, &spriteBatch->VBO);
    glDeleteBuffers(1, &spriteBatch->EBO);
    printf("ok3\n");

    free(spriteBatch->quadBuffer);    printf("ok4\n");

    free(spriteBatch->sampler);    printf("ok5\n");

    free(spriteBatch);printf("end\n");
}

void heroSpriteBatchBegin(HeroSpriteBatch* spriteBatch)
{
    heroShaderBind(spriteBatch->shader);
    glUniformMatrix4fv(spriteBatch->viewLoc, 1, GL_FALSE, (float*)(&(spriteBatch->viewMatrix.col[0])));
    glUniform1iv(spriteBatch->shaderTexturesLocation, spriteBatch->maxTextureSlots, spriteBatch->sampler);

    spriteBatch->quadBufferPtr = spriteBatch->quadBuffer;
}

void heroSpriteBatchEnd(HeroSpriteBatch* spriteBatch)
{
    GLsizeiptr size = (uint8_t*)spriteBatch->quadBufferPtr - (uint8_t*)spriteBatch->quadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, spriteBatch->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, spriteBatch->quadBuffer);

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
    for(int i = 0; i < spriteBatch->maxTextureSlots; i++)
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
    spriteBatch->quadBufferPtr->color = (HeroFloat4){ 1.0f, 1.0f, 1.0f, 1.0f };
    spriteBatch->quadBufferPtr++;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)(position.x + size.x), (float)position.y, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 1.0f, 0.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = (HeroFloat4){ 1.0f, 1.0f, 1.0f, 1.0f };
    spriteBatch->quadBufferPtr++;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)(position.x + size.x), (float)(position.y + size.y), 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 1.0f, 1.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = (HeroFloat4){ 1.0f, 1.0f, 1.0f, 1.0f };
    spriteBatch->quadBufferPtr++;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ (float)position.x, (float)(position.y + size.y), 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ 0.0f, 1.0f };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = (HeroFloat4){ 1.0f, 1.0f, 1.0f, 1.0f };
    spriteBatch->quadBufferPtr++;

    spriteBatch->indexCount += 6;
}

void heroSpriteBatchDrawTextureEx(HeroSpriteBatch* spriteBatch, const HeroTexture* texture, const HeroInt2 position, const HeroInt2 size, const HeroInt4 rect, float angle, HeroColor color)
{
    if(spriteBatch->indexCount >= spriteBatch->maxIndexCount || 
        spriteBatch->textureSlotIndex > spriteBatch->maxTextureSlots)
    {
        heroSpriteBatchEnd(spriteBatch);
        heroSpriteBatchBegin(spriteBatch);
    }

    float textureIndex = 0.0f;
    // check registred texture
    for(int i = 0; i < spriteBatch->maxTextureSlots; i++)
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

    HeroInt2 textureSize = heroTextureGetSize(texture);
    float rx0 = (float)rect.x / (float)textureSize.x;
    float rx1 = (float)rect.z / (float)textureSize.x;
    float ry0 = (float)rect.y / (float)textureSize.y;
    float ry1 = (float)rect.w / (float)textureSize.y;

    int middleX = position.x + (int)(size.x/2);
    int middleY = position.y + (int)(size.y/2);

    float rotx = (float)(position.x - middleX)*cos(angle) - (position.y - middleY)*sin(angle) + middleX;
    float roty = (float)(position.x - middleX)*sin(angle) + (position.y - middleY)*cos(angle) + middleY;

    HeroFloat4 newColor = (HeroFloat4){ (float)color.r/255.0f, (float)color.g/255.0f, (float)color.b/255.0f, (float)color.a/255.0f };

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ rotx, roty, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ rx0, ry0 };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = newColor;
    spriteBatch->quadBufferPtr++;

    rotx = (float)(position.x + size.x - middleX)*cos(angle) - (position.y - middleY)*sin(angle) + middleX;
    roty = (float)(position.x + size.x - middleX)*sin(angle) + (position.y - middleY)*cos(angle) + middleY;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ rotx, roty, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ rx1, ry0 };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = newColor;
    spriteBatch->quadBufferPtr++;
    
    rotx = (float)(position.x + size.x - middleX)*cos(angle) - (position.y + size.y - middleY)*sin(angle) + middleX;
    roty = (float)(position.x + size.x - middleX)*sin(angle) + (position.y + size.y - middleY)*cos(angle) + middleY;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ rotx, roty, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ rx1, ry1};
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = newColor;
    spriteBatch->quadBufferPtr++;

    rotx = (float)(position.x - middleX)*cos(angle) - (position.y + size.y - middleY)*sin(angle) + middleX;
    roty = (float)(position.x - middleX)*sin(angle) + (position.y + size.y - middleY)*cos(angle) + middleY;

    spriteBatch->quadBufferPtr->position = (HeroFloat3){ rotx, roty, 0.0f };
    spriteBatch->quadBufferPtr->texCoords = (HeroFloat2){ rx0, ry1 };
    spriteBatch->quadBufferPtr->texIndex = textureIndex;
    spriteBatch->quadBufferPtr->color = newColor;
    spriteBatch->quadBufferPtr++;

    spriteBatch->indexCount += 6;
}