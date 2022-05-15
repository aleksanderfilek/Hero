#pragma once

#include"../Core/Math.hpp"
#include"../Graphics/Spritebatch.hpp"
#include"../Core/Events.hpp"
#include"Anchor.hpp"

namespace Hero
{
namespace UI
{

enum class Event : uint8_t
{
  OnHover = 0,
  Hover = 1,
  OffHover = 2,
  OnLeftClick = 3,
  HoldLeftClick = 4,
  OffLeftClick = 5
};

class IGroup;

class HERO IElement
{
  friend class IGroup;

protected:
  IGroup* parent = nullptr;

  Int2 absolutePosition = Int2::zero();
  Int2 relativePosition = Int2::zero();
  Int2 size = Int2::zero();

  HorizontalAnchor horizontalAnchor = HorizontalAnchor::LEFT;
  VerticalAnchor verticalAnchor = VerticalAnchor::TOP;

  bool visible = true;

  uint8_t eventState;
  EventHandler eventHandlers[6];
  void* eventArgs[6]{nullptr};

public:
  HERO virtual ~IElement();

  virtual void draw(Spritebatch* spritebatch){};
  HERO virtual void update(Int2 mousePosition, uint8_t buttonState);
  HERO virtual void setAbsolutPosition(Int2 _absolutePosition);
  HERO virtual void setPosition(Int2 _position);
  HERO virtual void setSize(Int2 _size);
  HERO void setHorizontalAnchor(HorizontalAnchor NewHorizontalAnchor);
  HERO void setVerticalAnchor(VerticalAnchor NewVerticalAnchor);

  inline void setVisibility(bool _visible){ visible = _visible; }
  inline bool isVisible(){ return visible; }
  inline bool isEvent(UI::Event event){return eventState & (uint16_t)event; }
  inline Int2 getRelativePosition(){ return relativePosition; }
  inline Int2 getAbsolutePosition(){ return absolutePosition; }
  inline Int2 getSize(){ return size; }

  HERO void addEvent(Event type, EventFunction function, void* arg);
};

}
}