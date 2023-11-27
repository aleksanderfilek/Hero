#pragma once

#include "../../../Definitions.h"
#include "../../../GenericTypes/StringId.h"
#include "../InputKeys.h"

class HERO_API IInputDevice
{
public:
    virtual StringId GetId() = 0; 
    virtual bool ProcessEvent(void* Event, InputAction& Action) = 0;
};