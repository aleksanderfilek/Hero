#pragma once

#include"Math.hpp"
#include"IGroup.hpp"

#include<vector>

namespace Hero
{
namespace UI
{

class IElement;

class Widget : public IGroup
{
public:
  HERO Widget();
  HERO ~Widget();

  HERO void draw(Spritebatch* spritebatch) override;

  HERO bool add(const std::string& name, IElement* element);
  HERO bool remove(const std::string& name);
};

}
}