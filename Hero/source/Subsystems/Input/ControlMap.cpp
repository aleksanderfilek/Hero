#include "ControlMap.h"

void ControlMap::AddAction(StringId Id, InputActionDefinition Action)
{
    switch (Action.Category)
    {
    case InputCategory::MOUSE:
        mouseBindings.Add(Action.Key, Id);
        break;
    case InputCategory::KEYBOARD:
        keybordBindings.Add(Action.Key, Id);
        break;
    }
}

StringId ControlMap::GetId(const InputAction& Action)
{
    switch (Action.Category)
    {
    case InputCategory::MOUSE:
        if(mouseBindings.Contains(Action.Key))
        {
            return mouseBindings[Action.Key];
        }
        break;
    case InputCategory::KEYBOARD:
        if(keybordBindings.Contains(Action.Key))
        {
            return keybordBindings[Action.Key];
        }
        break;
    }

    return StringId((uint32_t)0);
}