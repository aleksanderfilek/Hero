#include"Image.hpp"

namespace Hero
{
namespace UI
{

HERO Image::~Image()
{
  if(free) delete texture;
}

HERO void Image::draw(Spritebatch* spritebatch)
{
  if(!visible) return;

  spritebatch->drawTexture(texture, absolutePosition, 0, size, rect);
}

HERO void Image::setTexture(Texture* _texture, bool _free)
{
  if(texture != nullptr && free == true)
  {
    delete texture;
  }

  free = _free;

  texture = _texture;
  if(rect == Float4::zero())
  {
    rect = (Float4){0.0f, 0.0f, 1.0f, 1.0f};
  }

  if(size == Int2::zero())
  {
    size = texture->getSize();
  }
}

}
}