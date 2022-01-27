#include"Label.hpp"

namespace Hero
{
namespace UI
{

HERO Label::~Label()
{
  delete texture;
  if(free) delete font;
}

HERO void Label::draw(Spritebatch* spritebatch)
{
  if(!visible) return;

  spritebatch->drawTexture(texture, texturePosition, textureSize, rect);
}

HERO void Label::setAlligment(Alligment _alligment)
{
  alligment = _alligment;
}

HERO void Label::setFont(Font* _font, bool _free)
{
  font = _font;
  free = _free;
}

HERO void Label::setColor(const ColorRGB& _color)
{
  color = _color;
}

HERO void Label::setText(const std::string& _text)
{
  text = _text;
}

HERO void Label::apply()
{
  if(texture != nullptr) delete texture;

  texture = new Texture(text.c_str(), color, font,
    (uint8_t)TextureFlag::LINEAR | (uint8_t)TextureFlag::NO_MIPMAP);

  Int2 texSize = texture->getSize();

  switch(alligment)
  {
    case Alligment::LEFT_TOP:
      texturePosition = absolutePosition;
    break;
    case Alligment::TOP:
      texturePosition.x = absolutePosition.x + (size.x - texSize.x)/2;
      texturePosition.y = absolutePosition.y;
    break;
    case Alligment::RIGHT_TOP:
      texturePosition.x = absolutePosition.x + size.x - texSize.x;
      texturePosition.y = absolutePosition.y;
    break;
    case Alligment::LEFT:
      texturePosition.x = absolutePosition.x;
      texturePosition.y = absolutePosition.y + (size.y - texSize.y)/2;
    break;
    case Alligment::CENTER:
      texturePosition.x = absolutePosition.x + (size.x - texSize.x)/2;
      texturePosition.y = absolutePosition.y + (size.y - texSize.y)/2;
    break;
    case Alligment::RIGHT:
      texturePosition.x = absolutePosition.x + size.x - texSize.x;
      texturePosition.y = absolutePosition.y + (size.y - texSize.y)/2;
    break;
    case Alligment::LEFT_BOTTOM:
      texturePosition.x = absolutePosition.x;
      texturePosition.y = absolutePosition.y + size.y - texSize.y;
    break;
    case Alligment::BOTTOM:
      texturePosition.x = absolutePosition.x + (size.x - texSize.x)/2;
      texturePosition.y = absolutePosition.y + size.y - texSize.y;
    break;
    case Alligment::RIGHT_BOTTOM:
      texturePosition.x = absolutePosition.x + size.x - texSize.x;
      texturePosition.y = absolutePosition.y + size.y - texSize.y;
    break;
  }

  int lpsx = texturePosition.x + texSize.x;
  int lpsy = texturePosition.y + texSize.y;
  int psx = texturePosition.x + size.x;
  int psy = texturePosition.y + size.y;

  rect.x = (texturePosition.x >= texturePosition.x)? 0 : texturePosition.x - texturePosition.x;
  rect.y = (texturePosition.y >= texturePosition.y)? 0 : texturePosition.y - texturePosition.y;
  rect.z = (lpsx <= psx)? texSize.x : texturePosition.x + size.x  - texturePosition.x;
  rect.w = (lpsy <= psy)? texSize.y : texturePosition.y + size.y  - texturePosition.y;
  rect.z /= texSize.x;
  rect.w /= texSize.y;

  textureSize.x = min(lpsx, psx);
  textureSize.x -= (texturePosition.x >= texturePosition.x)?texturePosition.x:texturePosition.x;
  textureSize.y = min(lpsy, psy);
  textureSize.y -= (texturePosition.y >= texturePosition.y)?texturePosition.y:texturePosition.y;

  texturePosition.x = max(texturePosition.x, texturePosition.x);
  texturePosition.y = max(texturePosition.y, texturePosition.y);
}

}
}