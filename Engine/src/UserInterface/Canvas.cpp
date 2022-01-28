#include"Canvas.hpp"

namespace Hero
{
namespace UI
{

HERO void Canvas::recalculate()
{
  for(auto it: children)
  {
    it.second->setAbsolutPosition(absolutePosition);
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