#pragma once 

#include"../Core/Math.hpp"

#include<cstdlib>

namespace Hero
{
  class Shader;
  class Texture;

  struct SpritebatchVertex
  {
    Float3 position;
    Float2 texCoords;
    float texIndex;
    Float4 color;
    float layer;
  };

  class Spritebatch
  {
  private:
    uint32_t spriteCapacity;

    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;

    SpritebatchVertex* quadBuffer;
    SpritebatchVertex* quadBufferPtr;

    uint32_t indexCount;
    uint32_t maxIndexCount;

    uint32_t maxTextureSlots;
    const Texture** textureSlots;
    uint32_t textureSlotIndex;
    uint32_t shaderTexturesLocation;

    int *sampler;

  public:
    HERO Spritebatch(uint32_t capacity, uint32_t maxTextures);
    HERO ~Spritebatch();

    HERO void begin();
    HERO void end();

    HERO void drawTexture(const Texture* texture, const Int2& position, int layer, const Int2& size, Float4 rect = (Float4){ 0.0f,0.0f,1.0f,1.0f });
  
    HERO void setShader(Shader* _shader);
  };
} // namespace Hero
