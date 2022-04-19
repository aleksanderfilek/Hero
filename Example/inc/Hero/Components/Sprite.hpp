#pragma once

#include"IComponent.hpp"
#include"Math.hpp"

namespace Hero
{

struct SpriteData : public IComponent
{
  class TransformData* transform = nullptr;
  Float4 rect = (Float4){ 0.0f,0.0f,1.0f,1.0f };
  bool visible = true;
  class Texture* texture = nullptr;
};

class Sprite : public IComponentSystem<SpriteData>
{
private:
  class Spritebatch* spritebatch;
  class Shader* shader;
  float pixelsPerUnit;

public:
  HERO Sprite(uint32_t chunkSize, class Shader* _shader, float pixelsPerUnit = 100.0f, uint32_t capacity = 100, uint32_t maxTextures = 32);
  HERO ~Sprite();

  HERO void update() override;

private:
  HERO void dataInit(SpriteData* data) override;
  HERO void dataUpdate(SpriteData* data) override;
  HERO void dataDestroy(SpriteData* data) override;
};

}