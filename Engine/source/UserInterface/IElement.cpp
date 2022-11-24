#include"IElement.hpp"
#include"IGroup.hpp"
#include<iostream>
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
  bool hover = pointBoxIntersection(mousePosition, GetAbsolutePosition(), GetAbsoluteSize());

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

HERO void IElement::UpdateAbsoluteTransform()
{
  std::cout<<"wow\n";
  Int2 ParentPosition = Int2::zero();
  Int2 ParentSize = Int2::zero();
  if(parent)
  {
    ParentPosition = parent->GetAbsolutePosition();
    ParentSize = parent->GetAbsoluteSize();
  }

  switch(horizontalAnchor)
  {
    case HorizontalAnchor::LEFT:
    case HorizontalAnchor::CENTER:
    case HorizontalAnchor::RIGHT:
    {
      int PivotPoint = relativeTransform.x + pivot.x * relativeTransform.z;

      absoluteTransform.x = anchor.x * ParentSize.x + PivotPoint;
      absoluteTransform.z = relativeTransform.z;
      }  break;
    case HorizontalAnchor::STRETCH:
      absoluteTransform.x = relativeTransform.x;
      absoluteTransform.z = ParentSize.x - relativeTransform.z - relativeTransform.x;
      break;
  }

  switch(verticalAnchor)
  {
    case VerticalAnchor::TOP:
    case VerticalAnchor::CENTER:
    case VerticalAnchor::BOTTOM:
    {
      int PivotPoint = relativeTransform.y + pivot.y * relativeTransform.w;

      absoluteTransform.y = anchor.y * ParentSize.y + PivotPoint;
      absoluteTransform.w = relativeTransform.w;
      }  break;
    case VerticalAnchor::STRETCH:
      absoluteTransform.y = relativeTransform.y;
      absoluteTransform.w = ParentSize.y - relativeTransform.w - relativeTransform.y;
      break;
  }

  absoluteTransform.x += ParentPosition.x;
  absoluteTransform.y += ParentPosition.y;

  std::cout<<absoluteTransform<<std::endl;
}

HERO void IElement::SetPivot(Float2 Pivot)
{
  pivot = Pivot;
  UpdateAbsoluteTransform();
}

HERO void IElement::SetRelativeTransform(Int4 Transform, 
  HorizontalAnchor NewHorizontalAnchor, VerticalAnchor NewVerticalAnchor)
{
  relativeTransform = Transform;

  horizontalAnchor = NewHorizontalAnchor;
  verticalAnchor = NewVerticalAnchor;

  switch(horizontalAnchor)
  {
    case HorizontalAnchor::LEFT:
      anchor.x = 0.0f;
      break;
    case HorizontalAnchor::CENTER:
      anchor.x = 0.5f;
      break;
    case HorizontalAnchor::RIGHT:
      anchor.x = 1.0f;
      break;
  }

  switch(verticalAnchor)
  {
    case VerticalAnchor::TOP:
      anchor.y = 0.0f;
      break;
    case VerticalAnchor::CENTER:
      anchor.y = 0.5f;
      break;
    case VerticalAnchor::BOTTOM:
      anchor.y = 1.0f;
      break;
  }
  
  UpdateAbsoluteTransform();
}

HERO Int4 IElement::GetRelativeTransform() const
{
  return relativeTransform;
}

HERO Int2 IElement::GetAbsolutePosition() const
{
  return Int2(absoluteTransform.x, absoluteTransform.y);
}

HERO Int2 IElement::GetAbsoluteSize() const
{
  return Int2(absoluteTransform.z, absoluteTransform.w);
}

HERO void IElement::addEvent(Event type, EventFunction function, void* arg)
{
  eventHandlers[(uint8_t)type].add(function);
  eventArgs[(uint8_t)type] = arg;
}

}
}