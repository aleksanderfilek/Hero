#pragma once

#include"Math.hpp"

namespace Hero
{
namespace UI
{

class IElement
{
protected:
  Int2 absolutePosition;
  Int2 relativePosition;
  Int2 size;

  bool visible;
public:
  HERO virtual ~IElement(){};
};

}
}