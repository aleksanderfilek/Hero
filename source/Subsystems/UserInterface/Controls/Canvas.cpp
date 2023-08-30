#include "Canvas.h"

void Canvas::_InternalSetWidget(class Widget* Widget)
{
    Control::_InternalSetWidget(Widget);

    for(Control* control: children)
    {
        delete control;
    }
}

void Canvas::Add(Control* Child)
{
    if(children.Contains(Child))
    {
        return;
    }
    children.Add(Child);
}

void Canvas::Remove(Control* Child)
{
    children.Remove(Child);
}

void Canvas::ClearChildren()
{
    for(Control* control: children)
    {
        delete control;
    }
    children.Clear();
}

int Canvas::GetChildrenCount()
{
    return children.Length();
}

void Canvas::GetChildren(Array<Control*>& Children)
{
    Children = children;
}

void Canvas::_InternalUpdateHoverState(const Int2& MousePosition)
{
    Control::_InternalUpdateHoverState(MousePosition);
    if(!IsHovered())
        return;

    for(Control* control: children)
    {
        control->_InternalUpdateHoverState(MousePosition);
    }
}

void Canvas::SetHover(bool Hovered)
{
    Control::SetHover(Hovered);

    for(Control* control: children)
    {
        control->SetHover(Hovered);
    }
}

bool Canvas::_InternalUpdateButtonClicks(MouseCode Code)
{
    if(!IsHovered())
        return false;

    for(int i = GetChildrenCount() - 1; i >= 0; i--)
    {
        bool result = children[i]->_InternalUpdateButtonClicks(Code);
        if(result)
            return true;
    }

    return Control::_InternalUpdateButtonClicks(Code);
}

void Canvas::Draw(class MultiTextureSpritebatch* Spritebatch)
{
    for(Control* control: children)
    {
        control->Draw(Spritebatch);
    }
}