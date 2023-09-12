#pragma once 

#include "../../Definitions.h"
#include "../../GenericTypes/StringId.h"
#include "../../Containers/Map.h"
#include "InputKeys.h"

struct InputActionDefinition
{
    InputCategory Category;
    uint32_t Key;

    InputActionDefinition(){}
    InputActionDefinition(InputCategory Category, KeyCode Code)
        : Category(Category), Key((uint32_t)Code){}
    InputActionDefinition(InputCategory Category, MouseCode Code)
        : Category(Category), Key((uint32_t)Code){}
};

class HERO_API ControlMap
{
private:
    Map<uint32_t, StringId> mouseBindings;
    Map<uint32_t, StringId> keybordBindings;

public:
    void AddAction(StringId Id, InputActionDefinition Action);
    StringId GetId(const InputAction& Action);
};