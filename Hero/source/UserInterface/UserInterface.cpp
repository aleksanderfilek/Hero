#include "UserInterface.h"
#include "Widget.h"
#include "../Subsystems/Input/InputSubsystem.h"
#include "../Subsystems/Input/Devices/MouseDevice.h"
#include "../Subsystems/Time/TimeSubsystem.h"
#include "../Subsystems/Resource/ResourceSubsystem.h"
#include "../Resources/Shader.h"
#include "../Subsystems/Window/WindowObject.h"
#include "../Graphics/RenderTarget.h"
#include "../Containers/Map.h"
#include "../Graphics/SpriteRenderer/IntermediateSpriteRenderer.h"

UserInterface::UserInterface(class WindowObject* Window)
    : window(Window)
{
     windowSize = window->GetConfiguration().Size;

     windowRenderTarget = window->GetWindowRenderTarget(StringId("UserInterface"));

     window->OnWindowEventResized.AddEvent(this, &UserInterface::ReactToWindowResized);

     MouseDevice* mouseDevice = (MouseDevice*)InputSubsystem::Get().GetDevice(StringId("Mouse"));
     mouseDevice->OnMouseMotion.AddEvent(this, &UserInterface::ReactToMouseMotion);
     mouseDevice->OnMouseClick.AddEvent(this, &UserInterface::ReactToMouseClick);

     spriteRenderer = new IntermediateSpriteRenderer();
}

UserInterface::~UserInterface()
{
     for(Widget* widget: widgets)
     {
         delete widget;
     }

     delete spriteRenderer;
}

void UserInterface::Update(float DeltaTime)
{
    for(Widget* widget: widgets)
    {
        widget->Update(DeltaTime);
    }

    windowRenderTarget->RenderTarget->BindBuffers();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    windowRenderTarget->RenderTarget->Clear();
    spriteRenderer->Start(windowSize);
    for(Widget* widget: widgets)
    {
        widget->Draw(spriteRenderer);
    }
    spriteRenderer->End();
    windowRenderTarget->RenderTarget->UnbindBuffers();
}

void UserInterface::ReactToWindowResized(class WindowObject* Window, Int2 Size)
{
    windowSize = Size;

    for (Widget* widget : widgets)
    {
        widget->_InternalResize(Size);
    }
}

void UserInterface::ReactToMouseMotion(const Int2& Position, const Int2& MotionVector)
{
    for(Widget* widget: widgets)
    {
        widget->_InternalUpdateHoverState(Position);
    }
}

void UserInterface::ReactToMouseClick(MouseCode Code, InputActionState State)
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

void UserInterface::AddWidget(Widget* Widget)
{
    widgets.Add(Widget);
    Widget->userInterface = this;
    Widget->Construct();
}

void UserInterface::RemoveWidget(Widget* Widget)
{
    widgets.Remove(Widget);
}