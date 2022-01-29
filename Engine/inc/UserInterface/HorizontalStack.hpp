#pragma once

#include"IGroup.hpp"

namespace Hero
{
namespace UI
{

class HorizontalStack : public IGroup
{
private:
  uint32_t spacing = 0;

public:
  HERO void recalculate() override;
  HERO bool add(const std::string& name, IElement* element) override;

  inline void setSpacing(uint32_t _spacing){ spacing = _spacing; }
  inline uint32_t getSpacing(){ return _spacing; }
};

}
}