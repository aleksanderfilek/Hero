#include "ControlScheme.h"

bool ControlScheme::ProcessAction(const StringId& Id, const InputAction& Action)
{
    if(!actions.Contains(Id))
    {
        return false;
    }

    actions[Id].Broadcast(Action.State);
    return true;
}