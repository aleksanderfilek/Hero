#include"Canvas.hpp"

namespace Hero
{
namespace UI
{

HERO bool Canvas::add(const std::string& name, IElement* element)
{
  bool result = IGroup::add(name, element);
  
  element->UpdateAbsoluteTransform();

  return result;
}


}
}