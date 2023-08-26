#pragma once 

#include "../../Definitions.h"
#include "../../GenericTypes/Event.h"
#include "../../GenericTypes/StringId.h"
#include "../../Containers/Map.h"
#include "InputKeys.h"

EVENT_DISPATCHER(InputActionEvent, InputActionState)

class HERO_API ControlScheme
{
private:
    Map<StringId, InputActionEvent> actions;

public:
    template<class UserClass>
    bool BindAction(const StringId& Id, UserClass* Object, void (UserClass::*MethodPtr)(InputActionState))
    {
        actions.Add(Id, InputActionEvent());
        InputActionEvent& actionEvent = actions[Id];
        actionEvent.AddEvent(Object, MethodPtr);
    }

    bool ProcessAction(const StringId& Id, const InputAction& Action);
};
