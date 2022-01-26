#include"IElement.hpp"
#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

HERO IElement::~IElement()
{
  
}

HERO void IElement::setPosition(Int2 _position)
{
  Int2 difference = substractI2(_position, relativePosition);
  absolutePosition = addI2(absolutePosition, difference);
  if(parent == nullptr) std::cout<<"NULL"<<std::endl;
  parent->recalculatePositions();
}

HERO void IElement::serSize(Int2 _size)
{
  size = _size;
  parent->recalculatePositions();
}

}
}