#pragma once

#include "../Definitions.h"
#include "../Containers/Map.h"
#include "../Containers/Array.h"
#include "../Math/Int2.h"
#include "../Subsystems/Input/InputKeys.h"

class HERO_API UserInterface
{
private:
    class WindowObject* window = nullptr;

public:
    UserInterface(class WindowObject* Window);
    ~UserInterface();
    void Update(float DeltaTime);

private:
    Array<class Widget*> widgets;

    void ReactToWindowResized(class WindowObject* Window, Int2 Size);
    void ReactToMouseMotion(const Int2& Position, const Int2& MotionVector);
    void ReactToMouseClick(MouseCode Code, InputActionState State);

public:
    void AddWidget(class Widget* Widget);
    void RemoveWidget(class Widget* Widget);

private:
    class Shader* shader = nullptr;
    void CreateAndRegisterShader();
    class WindowRenderTarget* windowRenderTarget = nullptr;
    class MultiTextureSpritebatch* spritebatch = nullptr;
};