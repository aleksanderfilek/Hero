#pragma once

#include"Math.hpp"
#include"Spritebatch.hpp"

namespace Hero
{

namespace UI
{

enum class Event : uint16_t
{
    OnHover = 1,
    Hover = 2,
    OffHover = 4,
    OnLeftClick = 8,
    HoldLeftClick = 16,
    OffLeftClick = 32
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

  uint16_t eventState;

public:
  HERO virtual ~IElement();

  virtual void draw(Spritebatch* spritebatch){};
  HERO virtual void update(Int2 mousePosition);
  HERO virtual void setAbsolutPosition(Int2 originPosition);
  HERO virtual void setPosition(Int2 _position);
  HERO virtual void setSize(Int2 _size);

  inline void setVisibility(bool _visible){ visible = _visible; }
  inline bool isVisible(){ return visible; }
  inline bool isEvent(UI::Event event){return eventState & (uint16_t)event; }
};

}
}