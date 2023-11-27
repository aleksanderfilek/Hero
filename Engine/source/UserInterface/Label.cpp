#include"Label.hpp"

#include <iostream>

namespace Hero
{
namespace UI
{

HERO Label::~Label()
{
  if(texture)
    delete texture;
}

HERO void Label::draw(Spritebatch* spritebatch)
{
  if(!visible) return;
  spritebatch->drawTexture(texture, texturePosition, 0, textureSize, rect);
}

HERO void Label::setAlligment(Alligment _alligment)
{
  alligment = _alligment;

  if(texture) calculateAlligment();
}

HERO void Label::setFont(Font* _font)
{
  font = _font;
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
  calculateAlligment();
}

HERO void Label::calculateAlligment()
{
  Int2 texSize = texture->getSize();
  Int2 absolutePosition = GetAbsolutePosition();
  Int2 absoluteSize = GetAbsoluteSize();

  switch(alligment)
  {
    case Alligment::LEFT_TOP:
      texturePosition = absolutePosition;
    break;
    case Alligment::TOP:
      texturePosition.x = absolutePosition.x + (absoluteSize.x - texSize.x)/2;
      texturePosition.y = absolutePosition.y;
    break;
    case Alligment::RIGHT_TOP:
      texturePosition.x = absolutePosition.x + absoluteSize.x - texSize.x;
      texturePosition.y = absolutePosition.y;
    break;
    case Alligment::LEFT:
      texturePosition.x = absolutePosition.x;
      texturePosition.y = absolutePosition.y + (absoluteSize.y - texSize.y)/2;
    break;
    case Alligment::CENTER:
      texturePosition.x = absolutePosition.x + (absoluteSize.x - texSize.x)/2;
      texturePosition.y = absolutePosition.y + (absoluteSize.y - texSize.y)/2;
    break;
    case Alligment::RIGHT:
      texturePosition.x = absolutePosition.x + absoluteSize.x - texSize.x;
      texturePosition.y = absolutePosition.y + (absoluteSize.y - texSize.y)/2;
    break;
    case Alligment::LEFT_BOTTOM:
      texturePosition.x = absolutePosition.x;
      texturePosition.y = absolutePosition.y + absoluteSize.y - texSize.y;
    break;
    case Alligment::BOTTOM:
      texturePosition.x = absolutePosition.x + (absoluteSize.x - texSize.x)/2;
      texturePosition.y = absolutePosition.y + absoluteSize.y - texSize.y;
    break;
    case Alligment::RIGHT_BOTTOM:
      texturePosition.x = absolutePosition.x + absoluteSize.x - texSize.x;
      texturePosition.y = absolutePosition.y + absoluteSize.y - texSize.y;
    break;
  }

  Float4 MinimumArea = { 
    max(texturePosition.x, absolutePosition.x), 
    max(texturePosition.y, absolutePosition.y),
    min(texturePosition.x + texSize.x, absolutePosition.x + absoluteSize.x),
    min(texturePosition.y + texSize.y, absolutePosition.y + absoluteSize.y)};

  Float4 TranslatedArea = {
    MinimumArea.x - texturePosition.x,
    MinimumArea.y - texturePosition.y,
    MinimumArea.z - texturePosition.x,
    MinimumArea.w - texturePosition.y};

  Float4 NormalizeArea = {
    TranslatedArea.x / texSize.x,
    TranslatedArea.y / texSize.y,
    TranslatedArea.z / texSize.x,
    TranslatedArea.w / texSize.y};

  rect = NormalizeArea;
  textureSize = {(float)(MinimumArea.z - MinimumArea.x), (float)(MinimumArea.w - MinimumArea.y)};
  texturePosition = {(float)MinimumArea.x, (float)MinimumArea.y};
}

HERO void Label::UpdateAbsoluteTransform()
{
  IElement::UpdateAbsoluteTransform();
  if(texture)
    calculateAlligment();
}

}
}