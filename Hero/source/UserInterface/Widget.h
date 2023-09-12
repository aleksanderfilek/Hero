#pragma once

#include "../Definitions.h"
#include "Controls/Canvas.h"
#include "../Containers/Array.h"

class HERO_API Widget
{
    friend class UserInterface;

private:
    class UserInterface* userInterface = nullptr;
    Canvas canvas;

public:
    virtual ~Widget(){}

    virtual void Construct();

    Canvas* GetCanvas();

    void _InternalUpdateHoverState(const Int2& MousePosition);
    bool _InternalUpdateButtonClicks(MouseCode Code);
    void _InternalResize(const Int2& Size);

private:
    Array<Control*> controlsToUpdate;
    Array<Control*> controlsToRemoveFromUpdate;

public:
    void AddControlToUpdate(Control* Control);
    void RemoveControlFromUpdate(Control* Control);
    virtual void Update(float DeltaTime);
    void Draw(class ISpriteRenderer* SpriteRenderer);
};