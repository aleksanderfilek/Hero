#include"Sprite.hpp"
#include"Spritebatch.hpp"
#include"Texture.hpp"
#include"Transform.hpp"
#include"Actor.hpp"

namespace Hero
{

HERO Sprite::Sprite(uint32_t chunkSize, class Shader* _shader, float pixelsPerUnit, uint32_t capacity, uint32_t maxTextures) 
  : IComponentSystem(chunkSize), pixelsPerUnit(pixelsPerUnit), shader(_shader)
{
  spritebatch = new Spritebatch(capacity, maxTextures);
  spritebatch->setShader(_shader);
}

HERO Sprite::~Sprite()
{
  delete spritebatch;
}

HERO void Sprite::update()
{
  shader->bind();
  IComponentSystem::update();
}

HERO void Sprite::dataInit(SpriteData* data)
{
  data->transform = (TransformData*)data->actor->GetComponent(SID("Transform"));
}

HERO void Sprite::dataUpdate(SpriteData* data)
{
  Float3 gPos = data->transform->getGlobalPosition();
  Int2 position = {(int)gPos.x, (int)gPos.y};
  Int2 size = data->texture->getSize();
  size.x = (int)((float)size.x/pixelsPerUnit);
  size.y = (int)((float)size.y/pixelsPerUnit);
  spritebatch->drawTexture(data->texture, position, (int)gPos.z, size, data->rect);
}

HERO void Sprite::dataDestroy(SpriteData* data)
{

}

}