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
  Int2 difference = _position - relativePosition;
  relativePosition = _position;
  absolutePosition = absolutePosition + difference;

  if(parent != nullptr) parent->recalculate();
}

HERO void IElement::setSize(Int2 _size)
{
  size = _size;

  if(parent != nullptr) parent->recalculate();
}

HERO void IElement::setHorizontalAnchor(HorizontalAnchor NewHorizontalAnchor)
{
  if(parent == nullptr)
    return;

  horizontalAnchor = NewHorizontalAnchor;

  float x = 0.0f;
  switch(horizontalAnchor)
  {
    case HorizontalAnchor::LEFT:
      x = absolutePosition.x - parent->absolutePosition.x;
      break;
    case HorizontalAnchor::CENTER:
      x = absolutePosition.x - parent->absolutePosition.x + (parent->size.x/2);
      break;
    case HorizontalAnchor::RIGHT:
      x = parent->absolutePosition.x + parent->size.x - absolutePosition.x;
      break;
  }

  relativePosition.x = x;

  parent->recalculate();
}

HERO void IElement::setVerticalAnchor(VerticalAnchor NewVerticalAnchor)
{
    if(parent == nullptr)
    return;
    
  verticalAnchor = NewVerticalAnchor;

  float y = 0.0f;
  switch(horizontalAnchor)
  {
    case HorizontalAnchor::LEFT:
      y = absolutePosition.y - parent->absolutePosition.y;
      break;
    case HorizontalAnchor::CENTER:
      y = absolutePosition.y - parent->absolutePosition.y + (parent->size.y/2);
      break;
    case HorizontalAnchor::RIGHT:
      y = parent->absolutePosition.y + parent->size.y - absolutePosition.y;
      break;
  }

  relativePosition.y = y;

  parent->recalculate();
}

HERO void IElement::addEvent(Event type, EventFunction function, void* arg)
{
  eventHandlers[(uint8_t)type].add(function);
  eventArgs[(uint8_t)type] = arg;
}

}
}