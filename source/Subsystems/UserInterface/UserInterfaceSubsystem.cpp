#include "UserInterfaceSubsystem.h"
#include "Widget.h"
#include "../Input/InputSubsystem.h"
#include "../Input/Devices/MouseDevice.h"
#include "../Time/TimeSubsystem.h"

UserInterfaceSubsystem* UserInterfaceSubsystem::instance = nullptr;

UserInterfaceSubsystem::UserInterfaceSubsystem()
{
    instance = this;

    updateEnabled = true;
}

void UserInterfaceSubsystem::Startup()
{
    MouseDevice* mouseDevice = (MouseDevice*)InputSubsystem::Get().GetDevice(StringId("Mouse"));
    mouseDevice->OnMouseMotion.AddEvent(this, &UserInterfaceSubsystem::ReactToMouseMotion);
    mouseDevice->OnMouseClick.AddEvent(this, &UserInterfaceSubsystem::ReactToMouseClick);
}

void UserInterfaceSubsystem::Shutdown()
{
    for(Widget* widget: widgets)
    {
        delete widget;
    }
}

void UserInterfaceSubsystem::Update()
{
    float deltaTime = TimeSubsystem::Get().GetDeltaTime();
    for(Widget* widget: widgets)
    {
        widget->Update(deltaTime);
    }
}

void UserInterfaceSubsystem::ReactToMouseMotion(const Int2& Position, const Int2& MotionVector)
{
    for(Widget* widget: widgets)
    {
        widget->_InternalUpdateHoverState(Position);
    }
}

void UserInterfaceSubsystem::ReactToMouseClick(MouseCode Code, InputActionState State)
{
    if(State == InputActionState::RELEASED)
        return;

    for(int i = widgets.Length() - 1; i >= 0; i--)
    {
        bool result = widgets[i]->_InternalUpdateButtonClicks(Code);
        if(result)
            return;
    }
}

void UserInterfaceSubsystem::AddWidget(Widget* Widget)
{
    widgets.Add(Widget);
}

void UserInterfaceSubsystem::RemoveWidget(Widget* Widget)
{
    widgets.Remove(Widget);
}

