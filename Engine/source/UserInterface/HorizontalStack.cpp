#include"HorizontalStack.hpp"

namespace Hero
{
namespace UI
{

HERO bool HorizontalStack::add(const std::string& name, IElement* element)
{
  bool result = IGroup::add(name, element);
  
  SetChildAnchors(childVerticalAnchor);

  return result;
}

HERO void HorizontalStack::SetChildAnchors(VerticalAnchor ChildVerticalAnchor)
{
  childVerticalAnchor = 
    (ChildVerticalAnchor != VerticalAnchor::STRETCH)? ChildVerticalAnchor : VerticalAnchor::TOP;

  Int2 Size = GetAbsoluteSize();

  float OffsetY = 0.0f;
  float OffsetX = 0.0f;

  switch(ChildVerticalAnchor)
  {
    case VerticalAnchor::TOP:
      OffsetY = (int)(0.0f * Size.y);
      break;
    case VerticalAnchor::CENTER:
      OffsetY = (int)(0.5f * Size.y);
      break;
    case VerticalAnchor::BOTTOM:
      OffsetY = (int)(1.0f * Size.y);
      break;
  }

  for(auto& element: children)
  {
    Int4 Transform = element.second->GetRelativeTransform();

    Transform.y = OffsetY;
    Transform.x = OffsetX;

    element.second->SetRelativeTransform(Transform, HorizontalAnchor::LEFT, childVerticalAnchor);

    OffsetX += Transform.z + spacing;
  }
}

}
}