#include "Control.h"
#include "../../Math/Intersections.h"
#include "../Widget.h"
#include "../UserInterface.h"
#include "../../Math/Math.h"

void Control::_InternalSetUserInterface(class UserInterface* UserInterface)
{
    userInterface = UserInterface;
}

class UserInterface* Control::GetUserInterface() const
{
    return userInterface;
}

void Control::_InternalSetWidget(class Widget* Widget)
{
    widget = Widget;
}

class Widget* Control::GetWidget() const
{
    return widget;
}

void Control::AttachToControl(Control* ControlToAttachTo)
{
    parent = ControlToAttachTo;
    _InternalSetUserInterface(parent->GetUserInterface());
    _InternalSetWidget(parent->GetWidget());

    _InternalUpdateTransforms();
}

Control* Control::GetParent() const
{
    return parent;
}

void Control::SetPosition(const Int2& Position)
{
    position = Position;

    if (parent)
    {
        _InternalUpdateTransforms();
    }
}

Int2 Control::GetPosition() const
{
    return position;
}

void Control::SetSize(const Int2& Size)
{
    size = Size;
    
    if (parent)
    {
        _InternalUpdateTransforms();
    }
}

Int2 Control::GetSize() const
{
    return size;
}

void Control::SetHorizontalAlligment(HorizontalAlligment Alligment)
{
    horizontalAlligment = Alligment;

    if(parent)
    {
        _InternalUpdateTransforms();
    }
}

HorizontalAlligment Control::GetHorizontalAlligment() const
{
    return horizontalAlligment;
}

void Control::SetVerticalAlligment(VerticalAlligment Alligment)
{
    verticalAlligment = Alligment;

    if(parent)
    {
        _InternalUpdateTransforms();
    }
}

VerticalAlligment Control::GetVerticalAlligment() const
{
    return verticalAlligment;
}

void Control::SetPivot(const Float2& Pivot)
{
    pivot = Pivot;

    if(parent)
    {
        _InternalUpdateTransforms();
    }
}

void Control::SetMinScale(float Scale)
{
    minScale = Scale;

    if (parent)
    {
        _InternalUpdateTransforms();
    }
}

float Control::GetMinScale() const
{
    return minScale;
}

void Control::SetMaxScale(float Scale)
{
    maxScale = Scale;

    if (parent)
    {
        _InternalUpdateTransforms();
    }
}

float Control::GetMaxScale() const
{
    return maxScale;
}

Int2 Control::GetAbsolutePosition() const
{
    return absolutePosition;
}

Int2 Control::GetAbsoluteSize() const
{
    return absoluteSize;
}

void Control::_InternalUpdateTransforms()
{
    Float2 anchor;

    switch(horizontalAlligment)
    {
    case HorizontalAlligment::LEFT:
        anchor.X = 0.0f;
        break;
    case HorizontalAlligment::CENTER:
        anchor.X = 0.5f;
        break;
    case HorizontalAlligment::RIGHT:
        anchor.X = 1.0f;
        break;
    }

    switch(verticalAlligment)
    {
    case VerticalAlligment::TOP:
        anchor.Y = 0.0f;
        break;
    case VerticalAlligment::CENTER:
        anchor.Y = 0.5f;
        break;
    case VerticalAlligment::BOTTOM:
        anchor.Y = 1.0f;
        break;
    }

    Int2 parentPosition;
    Int2 parentSize;
    if(parent)
    {
        parentPosition = parent->GetAbsolutePosition();
        parentSize = parent->GetAbsoluteSize();
    }

    Float2 windowScale = (userInterface)?userInterface->GetScale():Float2::One();
    float unclampedScale = max(windowScale.X, windowScale.Y);
    float clampedScale = Clamp(unclampedScale, minScale, maxScale);

    switch(horizontalAlligment)
    {
        case HorizontalAlligment::LEFT:
        case HorizontalAlligment::CENTER:
        case HorizontalAlligment::RIGHT:
        {
            int PivotPoint = position.X + pivot.X * size.X;

            absolutePosition.X = anchor.X * parentSize.X + PivotPoint * clampedScale;
            absoluteSize.X = size.X * clampedScale;
            }  break;
        case HorizontalAlligment::STRETCH:
            absolutePosition.X = position.X * clampedScale;
            absoluteSize.X = parentSize.X - (size.X + position.X) * clampedScale;
            break;
    }

    switch(verticalAlligment)
    {
        case VerticalAlligment::TOP:
        case VerticalAlligment::CENTER:
        case VerticalAlligment::BOTTOM:
        {
            int PivotPoint = position.Y + pivot.Y * size.Y;

            absolutePosition.Y = anchor.Y * parentSize.Y + PivotPoint * clampedScale;
            absoluteSize.Y = size.Y * clampedScale;
            }  break;
        case VerticalAlligment::STRETCH:
            absolutePosition.Y = position.Y;
            absoluteSize.Y = parentSize.Y - (size.Y + position.Y) * clampedScale;
            break;
    }

    absolutePosition.X += parentPosition.X;
    absolutePosition.Y += parentPosition.Y;
}

void Control::SetVisibility(VisibilityState Visibility)
{
    visibilityState = Visibility;

    if(parent)
    {
        parent->_InternalUpdateTransforms();
    }
}

void Control::_InternalUpdateHoverState(const Int2& MousePosition)
{
    bool result = Intersection::PointToRectangle(MousePosition, absolutePosition, absoluteSize);
    SetHover(result);
}

bool Control::IsHovered() const
{
    return hovered;
}

void Control::SetHover(bool Hovered)
{
    if(hovered == Hovered)
    {
        return;
    }

    hovered = Hovered;
    if(hovered)
        OnHoverEnter.Broadcast(this);
    else
        OnHoverExit.Broadcast(this);
}

bool Control::_InternalUpdateButtonClicks(MouseCode Code)
{
    if(!IsHovered())
        return false;

    switch (Code)
    {
        case MouseCode::LEFT:
            OnLeftClick.Broadcast(this);
            return OnLeftClick.size() > 0;
            break;
        case MouseCode::RIGHT:
            OnRightClick.Broadcast(this);
            return OnRightClick.size() > 0;
            break;
    }

    return false;
}

void Control::SetUpdateEnabled(bool Enable)
{
    if(updateEnabled == Enable)
        return;

    updateEnabled = Enable;

    if(updateEnabled)
        widget->AddControlToUpdate(this);
    else
        widget->RemoveControlFromUpdate(this);
}
