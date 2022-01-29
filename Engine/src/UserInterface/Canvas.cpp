#include"Canvas.hpp"

namespace Hero
{
namespace UI
{

HERO void Canvas::recalculate()
{
  for(auto it: children)
  {
    Int2 position = addI2(absolutePosition, it.second->getRelativePosition());
    it.second->setAbsolutPosition(position);
  }

  IGroup::recalculate();
}

HERO bool Canvas::add(const std::string& name, IElement* element)
{
  IGroup::add(name, element);
  
  recalculate();
}


}
}