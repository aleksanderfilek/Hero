#pragma once

#include "../../Definitions.h"
#include "Controls/Canvas.h"
#include "../../Containers/Array.h"

class HERO_API Widget
{
private:
    Canvas canvas;

public:
    virtual void Construct();

    void _InternalUpdateHoverState(const Int2& MousePosition);
    bool _InternalUpdateButtonClicks(MouseCode Code);

private:
    Array<Control*> controlsToUpdate;
    Array<Control*> controlsToRemoveFromUpdate;

public:
    void AddControlToUpdate(Control* Control);
    void RemoveControlFromUpdate(Control* Control);
    virtual void Update(float DeltaTime);

};