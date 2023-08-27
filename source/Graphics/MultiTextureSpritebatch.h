#pragma once 

#include "../Definitions.h"
#include "../Math/Int2.h"
#include "../Math/Float2.h"
#include "../Math/Float3.h"
#include "../Math/Float4.h"
#include "Color.h"
#include <cstdint>


  struct MultiTextureSpritebatchVertex
  {
    Float3 Position;
    Float2 TexCoords;
    float TexIndex;
    Color Color;
  };

  class HERO_API MultiTextureSpritebatch
  {
  private:
    uint32_t spriteCapacity;

    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;

    MultiTextureSpritebatchVertex* quadBuffer;
    MultiTextureSpritebatchVertex* quadBufferPtr;

    uint32_t indexCount;
    uint32_t maxIndexCount;

    uint32_t maxTextureSlots;
    const class Texture** textureSlots;
    uint32_t textureSlotIndex;
    uint32_t shaderTexturesLocation;

    int *sampler;
    uint32_t* indices;

  public:
    MultiTextureSpritebatch(uint32_t Capacity, uint32_t MaxTextures);
    ~MultiTextureSpritebatch();

    void Begin();
    void End();

    void DrawTexture(const class Texture* Texture, const Int2& Position, const Int2& Size, Float4 Rect = { 0.0f,0.0f,1.0f,1.0f }, const Color& color = COLOR_WHITE);
  
    void SetShader(class Shader* Shader);
  };
