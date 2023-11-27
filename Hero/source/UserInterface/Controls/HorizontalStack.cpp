#include"HorizontalStack.h"

void HorizontalStack::Add(Control* Child)
{
    Canvas::Add(Child);

    _InternalUpdateTransforms();
}

void HorizontalStack::Remove(Control* Child)
{
    Canvas::Remove(Child);

    _InternalUpdateTransforms();
}

void HorizontalStack::SetSpacing(uint32_t Spacing)
{
    spacing = Spacing;
}

void HorizontalStack::_InternalUpdateTransforms()
{
    Canvas::_InternalUpdateTransforms();

    Int2 Size = GetAbsoluteSize();

    float OffsetX = 0.0f;

    for (auto& element : children)
    {
        if (element->GetVisibility() == VisibilityState::HIDDEN)
        {
            continue;
        }

        Int2 elementPosition = element->GetPosition();

        elementPosition.X = OffsetX;

        element->SetPosition(elementPosition);
        element->SetHorizontalAlligment(HorizontalAlligment::LEFT);
        element->SetVerticalAlligment(VerticalAlligment::TOP);

        OffsetX += element->GetSize().X + spacing;
    }
}