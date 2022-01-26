#pragma once

#include"IElement.hpp"
#include"Texture.hpp"

namespace Hero
{
namespace UI
{

class HERO Image : public IElement
{
private:
  Texture* texture = nullptr;
  Float4 rect = Float4::zero();

public:
  HERO ~Image();

  HERO void draw(Spritebatch* spritebatch) override;

  HERO void setTexture(Texture* _texture);
  inline Texture* getTexture(){ return texture; }
  inline void setRect(Float4 _rect){ rect = _rect; }
  inline Float4 getRect(){ return rect; }
};

}
}