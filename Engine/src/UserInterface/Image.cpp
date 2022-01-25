#include"Image.hpp"

namespace Hero
{
namespace UI
{

HERO Image::~Image()
{

}

HERO void Image::draw(Spritebatch* spritebatch)
{
  if(!visible) return;

  spritebatch->drawTexture(texture, absolutePosition, size, rect);
}

HERO void Image::setTexture(Texture* _texture)
{
  if(texture != nullptr)
  {
    delete texture;
  }

  texture = _texture;
  if(rect == Float4::zero())
  {
    rect = (Float4){0.0f, 0.0f, 1.0f, 1.0f};
  }

  if(size == Int2::zero())
  {
    Int2 _size = texture->getSize();
    size = _size;
  }
}

}
}