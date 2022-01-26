#include"Canvas.hpp"

namespace Hero
{
namespace UI
{

HERO void Canvas::recalculatePositions()
{
  for(auto it: children)
  {
    it.second->setAbsolutPosition(absolutePosition);
  }
}

HERO bool Canvas::add(const std::string& name, IElement* element)
{
  IGroup::add(name, element);

  element->setAbsolutPosition(absolutePosition);
}


}
}