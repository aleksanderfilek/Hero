#include"IElement.hpp"
#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

HERO IElement::~IElement()
{
  
}

HERO void IElement::update(Int2 mousePosition)
{
  bool hover = pointBoxIntersection(mousePosition, absolutePosition, size);

  if(hover)
  {
    if(!(eventState & 1<<(uint8_t)Event::OnHover))
    {
      eventState |= 1<<(uint8_t)Event::OnHover;
    }
    else 
    {
      eventState |= 1<<(uint8_t)Event::Hover;
      eventState &=~(1<<(uint8_t)Event::OnHover);
    }
  }
  else
  {
    if(eventState & 1<<(uint8_t)Event::Hover)
    {
      eventState |= 1<<(uint8_t)Event::OffHover;
      eventState &=~(1<<(uint8_t)Event::Hover);
    }
    else if(eventState & 1<<(uint8_t)Event::OffHover)
    {
      eventState &= ~(1<<(uint8_t)Event::OffHover);
    }
  }

  for(int i = 7; i >=0; i--)
  {
    int num = (eventState & 1<<i)?1:0;
    std::cout<<num;
  }
  std::cout<<std::endl;

}

HERO void IElement::setAbsolutPosition(Int2 originPosition)
{
  absolutePosition = addI2(originPosition, relativePosition);
}

HERO void IElement::setPosition(Int2 _position)
{
  Int2 difference = substractI2(_position, relativePosition);
  relativePosition = _position;
  absolutePosition = addI2(absolutePosition, difference);

  if(parent != nullptr) parent->recalculate();
}

HERO void IElement::setSize(Int2 _size)
{
  size = _size;

  if(parent != nullptr) parent->recalculate();
}

}
}