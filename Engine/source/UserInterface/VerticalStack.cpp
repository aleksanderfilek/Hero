#include"VerticalStack.hpp"

namespace Hero
{
namespace UI
{

HERO bool VerticalStack::add(const std::string& name, IElement* element)
{
  bool result = IGroup::add(name, element);
  
  SetChildAnchors(childHorizontalAnchor);

  return result;
}

HERO void VerticalStack::SetChildAnchors(HorizontalAnchor ChildHorizontalAnchor)
{
  childHorizontalAnchor = 
    (ChildHorizontalAnchor != HorizontalAnchor::STRETCH)? ChildHorizontalAnchor : HorizontalAnchor::LEFT;

  Int2 Size = GetAbsoluteSize();

  float OffsetY = 0.0f;
  float OffsetX = 0.0f;

  switch(childHorizontalAnchor)
  {
    case HorizontalAnchor::LEFT:
      OffsetX = (int)(0.0f * Size.x);
      break;
    case HorizontalAnchor::CENTER:
      OffsetX = (int)(0.5f * Size.x);
      break;
    case HorizontalAnchor::RIGHT:
      OffsetX = (int)(1.0f * Size.x);
      break;
  }

  for(auto& element: children)
  {
    Int4 Transform = element->GetRelativeTransform();

    Transform.y = OffsetY;
    Transform.x = OffsetX;

    element->SetRelativeTransform(Transform, childHorizontalAnchor, VerticalAnchor::TOP);

    OffsetY += Transform.w + spacing;
  }
}

}
}