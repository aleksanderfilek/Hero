#pragma once

#include"IElement.hpp"
#include"Texture.hpp"
#include"Font.hpp"
#include"Alligment.hpp"
#include"Color.hpp"

#include<string>

namespace Hero
{
namespace UI
{

class HERO Label : public IElement
{
private:
  std::string text = "";
  Texture* texture = nullptr;
  Float4 rect = Float4::zero();
  Int2 textureSize = Int2::zero();
  Int2 texturePosition = Int2::zero();
  Alligment alligment = Alligment::LEFT_TOP;
  Font* font = nullptr;
  ColorRGB color = ColorRGB::white();
  bool free;

  HERO void calculateAlligment();

public:
  HERO ~Label();

  HERO void setAbsolutPosition(Int2 originPosition) override;
  HERO void setPosition(Int2 _position) override;
  HERO void draw(Spritebatch* spritebatch) override;
  HERO void setAlligment(Alligment _alligment);
  HERO void setFont(Font* _font, bool _free = true);
  HERO void setColor(const ColorRGB& _color);
  HERO void setText(const std::string& _text);
  HERO void apply();

  inline std::string getText(){ return text; }
};

}
}