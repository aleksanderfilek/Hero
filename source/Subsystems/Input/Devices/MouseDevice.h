#pragma once

#include "IInputDevice.h"
#include "../../../GenericTypes/Event.h"
#include "../../../Math/Int2.h"

EVENT_DISPATCHER(MouseMotionEvent, const Int2&, const Int2&);
EVENT_DISPATCHER(MouseWheelEvent, float);

class HERO_API MouseDevice : public IInputDevice
{
public:
    virtual StringId GetId() override { return StringId("Mouse"); }
    virtual bool ProcessEvent(void* Event, InputAction& Action) override;

    MouseMotionEvent OnMouseMotion;
    MouseWheelEvent OnMouseWheelEvent;
};