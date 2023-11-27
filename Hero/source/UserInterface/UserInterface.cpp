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

UserInterface::UserInterface(class WindowObject* Window, Int2 ReferenceSize)
    : window(Window), referenceSize(ReferenceSize)
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

Float2 UserInterface::GetScale() const
{
    Int2 size = window->GetConfiguration().Size;
    return { (float)size.X / (float)referenceSize.X, (float)size.Y / (float)referenceSize.Y };
}

void UserInterface::Update(float DeltaTime)
{
    for (class Widget* widget : widgetsToRemove)
    {
        widgets.Remove(widget);
        delete widget;
    }
    widgetsToRemove.Clear();

    for (class Widget* widget : widgetsToAdd)
    {
        widgets.Add(widget);
    }
    widgetsToAdd.Clear();

    for(Widget* widget: widgets)
    {
        widget->Update(DeltaTime);
    }

    windowRenderTarget->RenderTarget->BindBuffers();
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    windowRenderTarget->RenderTarget->Clear();
    spriteRenderer->Start(windowSize);
    for(Widget* widget: widgets)
    {
        widget->Draw(spriteRenderer);
    }
    glDisable(GL_BLEND);
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
    Widget->userInterface = this;
    Widget->Construct();
    widgetsToAdd.Add(Widget);
}

void UserInterface::RemoveWidget(Widget* Widget)
{
    widgetsToRemove.Add(Widget);
}