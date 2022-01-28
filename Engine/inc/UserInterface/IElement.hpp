#pragma once

#include"Math.hpp"
#include"Spritebatch.hpp"
#include"Events.hpp"

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
  IGroup* parent;

  Int2 absolutePosition = Int2::zero();
  Int2 relativePosition = Int2::zero();
  Int2 size = Int2::zero();

  bool visible = true;

  uint8_t eventState;
  EventHandler eventHandlers[6];
  void* eventArgs[6]{nullptr};
public:
  HERO virtual ~IElement();

  virtual void draw(Spritebatch* spritebatch){};
  HERO virtual void update(Int2 mousePosition, uint8_t buttonState);
  HERO virtual void setAbsolutPosition(Int2 originPosition);
  HERO virtual void setPosition(Int2 _position);
  HERO virtual void setSize(Int2 _size);

  inline void setVisibility(bool _visible){ visible = _visible; }
  inline bool isVisible(){ return visible; }
  inline bool isEvent(UI::Event event){return eventState & (uint16_t)event; }

  HERO void addEvent(Event type, EventFunction function, void* arg);
};

}
}