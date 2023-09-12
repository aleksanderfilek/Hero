#include "Widget.h"
#include "UserInterface.h"
#include "../Subsystems//Window/WindowObject.h"

void Widget::Construct()
{
    canvas._InternalSetWidget(this);
    canvas.SetSize(userInterface->GetWindow()->GetConfiguration().Size);
    canvas._InternalUpdateTransforms();
}

Canvas* Widget::GetCanvas()
{
    return &canvas;
}

void Widget::_InternalUpdateHoverState(const Int2& MousePosition)
{
    canvas._InternalUpdateHoverState(MousePosition);
}

bool Widget::_InternalUpdateButtonClicks(MouseCode Code)
{
    return canvas._InternalUpdateButtonClicks(Code);
}

void Widget::_InternalResize(const Int2& Size)
{
    canvas.SetSize(Size);
}

void Widget::AddControlToUpdate(Control* Control)
{
    controlsToUpdate.Add(Control);
}

void Widget::RemoveControlFromUpdate(Control* Control)
{
    controlsToRemoveFromUpdate.Add(Control);
}

void Widget::Update(float DeltaTime)
{   
    for(Control* control : controlsToRemoveFromUpdate)
    {
        controlsToUpdate.Remove(control);
    }
    controlsToRemoveFromUpdate.Clear();

    for(Control* control : controlsToUpdate)
    {
        control->Update(DeltaTime);
    }
}

void Widget::Draw(class ISpriteRenderer* SpriteRenderer)
{
    canvas.Draw(SpriteRenderer);
}