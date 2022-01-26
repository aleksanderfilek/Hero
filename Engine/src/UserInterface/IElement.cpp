#include"IElement.hpp"
#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

HERO IElement::~IElement()
{
  
}

HERO void IElement::setAbsolutPosition(Int2 originPosition)
{
  absolutePosition = addI2(originPosition, relativePosition);
}

HERO void IElement::setPosition(Int2 _position)
{
  Int2 difference = substractI2(_position, relativePosition);
  absolutePosition = addI2(absolutePosition, difference);

  if(parent != nullptr) parent->recalculatePositions();
}

HERO void IElement::setSize(Int2 _size)
{
  size = _size;

  if(parent != nullptr) parent->recalculatePositions();
}

}
}