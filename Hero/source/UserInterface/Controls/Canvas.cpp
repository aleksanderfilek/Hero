#include "Canvas.h"
#include <iostream>

Canvas::~Canvas()
{
    ClearChildren();
}

void Canvas::_InternalSetUserInterface(class UserInterface* UserInterface)
{
    Control::_InternalSetUserInterface(UserInterface);
    for (Control* control : children)
    {
        control->_InternalSetUserInterface(UserInterface);
    }
}

void Canvas::_InternalSetWidget(class Widget* Widget)
{
    Control::_InternalSetWidget(Widget);

    for(Control* control: children)
    {
        control->_InternalSetWidget(Widget);
    }
}

void Canvas::_InternalUpdateTransforms()
{
    Control::_InternalUpdateTransforms();

    for(Control* control: children)
    {
        control->_InternalUpdateTransforms();
    }
}

void Canvas::Add(Control* Child)
{
    if(children.Contains(Child))
    {
        return;
    }
    children.Add(Child);
    Child->AttachToControl(this);
    Child->_InternalUpdateTransforms();
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

void Canvas::Draw(class ISpriteRenderer* SpriteRenderer)
{
    for(int i = 0; i < children.Length(); i++)
    {
        children[i]->Draw(SpriteRenderer);
    }
}