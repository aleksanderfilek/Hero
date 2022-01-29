#include"IElement.hpp"
#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

#define binaryState(state) 1<<(uint8_t)state

HERO IElement::~IElement()
{
  
}

HERO void IElement::update(Int2 mousePosition, uint8_t buttonState)
{
  bool hover = pointBoxIntersection(mousePosition, absolutePosition, size);

  if(hover)
  {
    if(eventState & binaryState(Event::OnHover))
    {
      eventState |= binaryState(Event::Hover);
      eventState &= ~(binaryState(Event::OnHover));
    }
    else if(!(eventState & binaryState(Event::Hover)))
    {
      eventState &= ~(binaryState(Event::OffHover));
      eventState |= binaryState(Event::OnHover);
    }
  }
  else
  {
    bool isHovering = eventState & binaryState(Event::OnHover) 
      || eventState & binaryState(Event::Hover);
    bool isClick = eventState & binaryState(Event::OnLeftClick) || 
        eventState & binaryState(Event::OnLeftClick);
    eventState = 0;
    if(isHovering && !(eventState & binaryState(Event::OffHover))){
      eventState |= binaryState(Event::OffHover);
      if(isClick)
      {
        eventState |= binaryState(Event::OffLeftClick);
      }
    }
  }

  if(eventState & binaryState(Event::OnHover) 
    || eventState & binaryState(Event::Hover))
  {
    eventState &= 0x07;
    eventState |= buttonState<<3;
  }

  for(int i = 0; i < 8; i++)
  {
    if(eventState & 1<<i)
    {
      eventHandlers[i].invoke(this, eventArgs[i], 1);
    }
  }
}

HERO void IElement::setAbsolutPosition(Int2 _absolutePosition)
{
  absolutePosition = _absolutePosition;
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

HERO void IElement::addEvent(Event type, EventFunction function, void* arg)
{
  eventHandlers[(uint8_t)type].add(function);
  eventArgs[(uint8_t)type] = arg;
}

}
}