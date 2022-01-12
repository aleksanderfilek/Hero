#pragma once 

#include"Math.hpp"

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
    Texture** textureSlots;
    uint32_t textureSlotIndex;
    uint32_t shaderTexturesLocation;

    int *sampler;

  public:
    Spritebatch(Shader& shader, uint32_t capacity, uint32_t maxTextures);
    ~Spritebatch();

    void begin();
    void end();

    void drawTexture(Texture& texture, const Int2& position, const Int2& size, Float4 rect = (Float4){ 0.0f,0.0f,1.0f,1.0f });
  };
} // namespace Hero
