#pragma once

#include "IInputDevice.h"

class HERO_API KeyboardDevice : public IInputDevice
{
public:
    virtual StringId GetId() override { return StringId("Keyboard"); }
    virtual bool ProcessEvent(void* Event, InputAction& Action) override;
};