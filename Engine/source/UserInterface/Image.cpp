#include"Image.hpp"
#include<iostream>
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
  spritebatch->drawTexture(texture, GetAbsolutePosition(), 0, GetAbsoluteSize(), rect);
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

  if(GetAbsoluteSize() == Int2::zero())
  {
    if(horizontalAnchor != HorizontalAnchor::STRETCH)
      relativeTransform.z = texture->getSize().x;

    if(verticalAnchor != VerticalAnchor::STRETCH)
      relativeTransform.w = texture->getSize().y;
  }

  UpdateAbsoluteTransform();
}

}
}