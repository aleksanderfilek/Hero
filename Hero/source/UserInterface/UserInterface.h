#pragma once

#include "../Definitions.h"
#include "../Containers/Array.h"
#include "../Math/Int2.h"
#include "../Math/Float2.h"
#include "../Subsystems/Input/InputKeys.h"
#include "../GenericTypes/StringId.h"

class HERO_API UserInterface
{
private:
    class WindowObject* window = nullptr;

public:
    UserInterface(class WindowObject* Window);
    ~UserInterface();

    class WindowObject* GetWindow() const { return window; }

    void Update(float DeltaTime);

private:
    Array<class Widget*> widgets;
    Array<class Widget*> widgetsToAdd;
    Array<class Widget*> widgetsToRemove;

    void ReactToWindowResized(class WindowObject* Window, Int2 Size);
    void ReactToMouseMotion(const Int2& Position, const Int2& MotionVector);
    void ReactToMouseClick(MouseCode Code, InputActionState State);

public:
    void AddWidget(class Widget* Widget);
    void RemoveWidget(class Widget* Widget);

private:
    class ISpriteRenderer* spriteRenderer = nullptr;
    Int2 windowSize;
    class WindowRenderTarget* windowRenderTarget = nullptr;
};