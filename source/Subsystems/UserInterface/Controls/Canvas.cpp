#include "Canvas.h"

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

void Canvas::SetHover(bool Hovered)
{
    Control::SetHover(Hovered);

    for(Control* control: children)
    {
        control->SetHover(Hovered);
    }
}