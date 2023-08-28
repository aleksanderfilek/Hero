#include "UserInterfaceSubsystem.h"
#include "Widget.h"
#include "../Input/InputSubsystem.h"
#include "../Input/Devices/MouseDevice.h"

UserInterfaceSubsystem* UserInterfaceSubsystem::instance = nullptr;

UserInterfaceSubsystem::UserInterfaceSubsystem()
{
    instance = this;
}

void UserInterfaceSubsystem::Startup()
{
    MouseDevice* mouseDevice = (MouseDevice*)InputSubsystem::Get().GetDevice(StringId("Mouse"));
    mouseDevice->OnMouseMotion.AddEvent(this, &UserInterfaceSubsystem::ReactToMouseMotion);
}

void UserInterfaceSubsystem::Shutdown()
{

}

void UserInterfaceSubsystem::Update()
{

}

void UserInterfaceSubsystem::ReactToMouseMotion(const Int2& Position, const Int2& MotionVector)
{

}

void UserInterfaceSubsystem::AddWidget(Widget* Widget)
{
    widgets.Add(Widget);
}

void UserInterfaceSubsystem::RemoveWidget(Widget* Widget)
{
    widgets.Remove(Widget);
}

