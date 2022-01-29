#pragma once

namespace Hero
{
namespace UI
{

class VerticalStack : public IGroup
{
private:
  uint32_t spacing = 0;
  
public:
  HERO void recalculate() override;
  HERO bool add(const std::string& name, IElement* element) override;
};
}
}