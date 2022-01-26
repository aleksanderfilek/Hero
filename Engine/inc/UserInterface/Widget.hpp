#pragma once

#include"Math.hpp"
#include"IGroup.hpp"

#include<vector>

namespace Hero
{
namespace UI
{

class IElement;

class HERO Widget : public IGroup
{
public:
  HERO void draw(Spritebatch* spritebatch) override;
};

}
}