#include"HorizontalStack.hpp"

namespace Hero
{
namespace UI
{

HERO void HorizontalStack::recalculate()
{
  int x = absolutePosition.x;

  for(auto it: children)
  {
    it.second->absolutePosition = {x, absolutePosition.y};
    x += it.second->size.x + spacing;
  }

  IGroup::recalculate();
}

HERO bool HorizontalStack::add(const std::string& name, IElement* element)
{
  IGroup::add(name, element);
  
  recalculate();
}

}
}