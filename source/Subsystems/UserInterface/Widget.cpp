#include "Widget.h"

void Widget::Construct()
{
    canvas._InternalSetWidget(this);
}

void Widget::_InternalUpdateHoverState(const Int2& MousePosition)
{
    canvas._InternalUpdateHoverState(MousePosition);
}

bool Widget::_InternalUpdateButtonClicks(MouseCode Code)
{
    return canvas._InternalUpdateButtonClicks(Code);
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

void Widget::Draw(class MultiTextureSpritebatch* Spritebatch)
{
    canvas.Draw(Spritebatch);
}