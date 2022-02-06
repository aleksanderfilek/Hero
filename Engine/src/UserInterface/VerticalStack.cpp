#include"VerticalStack.hpp"

namespace Hero
{
namespace UI
{

HERO void VerticalStack::recalculate()
{
  int y = absolutePosition.y;

  for(auto it: children)
  {
    it.second->setAbsolutPosition({absolutePosition.x, y});
    y += it.second->getSize().y + spacing;
  }

  IGroup::recalculate();
}

HERO bool VerticalStack::add(const std::string& name, IElement* element)
{
  bool result = IGroup::add(name, element);
  
  recalculate();

  return result;
}

}
}