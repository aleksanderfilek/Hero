#pragma once

#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

class VerticalStack : public IGroup
{
private:
  uint32_t spacing = 0;

  HorizontalAnchor childHorizontalAnchor = HorizontalAnchor::LEFT;

public:
  HERO VerticalStack();
  ~VerticalStack() = default;

  HERO bool add(const std::string& name, IElement* element) override;

  HERO void SetChildAnchors(HorizontalAnchor ChildHorizontalAnchor);

  inline void setSpacing(uint32_t _spacing){ spacing = _spacing; }
  inline uint32_t getSpacing(){ return spacing; }
};
}
}