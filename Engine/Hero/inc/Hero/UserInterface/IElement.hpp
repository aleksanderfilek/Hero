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

  Int4 relativeTransform = Int4::zero();
  Int4 absoluteTransform = Int4::zero();
  Float2 pivot = Float2::zero();
  Float2 anchor = Float2::zero();
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

  HERO void SetPivot(Float2 Pivot);
  HERO void SetRelativeTransform(Int4 Transform, 
    HorizontalAnchor NewHorizontalAnchor = HorizontalAnchor::LEFT, 
    VerticalAnchor NewVerticalAnchor = VerticalAnchor::TOP);
  HERO Int4 GetRelativeTransform() const;
  HERO Int2 GetAbsolutePosition() const;
  HERO Int2 GetAbsoluteSize() const;
  HERO void UpdateAbsoluteTransform();

  inline void setVisibility(bool _visible){ visible = _visible; }
  inline bool isVisible(){ return visible; }
  inline bool isEvent(UI::Event event){return eventState & (uint16_t)event; }

  HERO void addEvent(Event type, EventFunction function, void* arg);
};

}
}