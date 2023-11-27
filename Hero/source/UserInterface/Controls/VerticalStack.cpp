#include"VerticalStack.h"

void VerticalStack::Add(Control* Child)
{
    Canvas::Add(Child);

    _InternalUpdateTransforms();
}

void VerticalStack::Remove(Control* Child)
{
    Canvas::Remove(Child);

    _InternalUpdateTransforms();
}

void VerticalStack::SetSpacing(uint32_t Spacing)
{ 
    spacing = Spacing;
}

void VerticalStack::_InternalUpdateTransforms()
{
    Canvas::_InternalUpdateTransforms();

    Int2 Size = GetAbsoluteSize();

    float OffsetY = 0.0f;

    for (auto& element : children)
    {
        if (element->GetVisibility() == VisibilityState::HIDDEN)
        {
            continue;
        }

        Int2 elementPosition = element->GetPosition();

        elementPosition.Y = OffsetY;

        element->SetPosition(elementPosition);
        element->SetHorizontalAlligment(HorizontalAlligment::LEFT);
        element->SetVerticalAlligment(VerticalAlligment::TOP);

        OffsetY += element->GetSize().Y + spacing;
    }
}