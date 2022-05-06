#include"Sprite.hpp"
#include"../Graphics/Spritebatch.hpp"
#include"../Graphics/Texture.hpp"
#include"Transform.hpp"
#include"Actor.hpp"
#include"../Graphics/Shader.hpp"
#include"../Systems/Window.hpp"

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
  spritebatch->begin();
  IComponentSystem::update();
  spritebatch->end();
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
  size.x = (int)((float)size.x);
  size.y = (int)((float)size.y);
  spritebatch->drawTexture(data->texture, position, 256, size, data->rect);
}

HERO void Sprite::dataDestroy(SpriteData* data)
{

}

}