#include "KeyboardDevice.h"
#include "../../../ThirdParty/SDL2/SDL.h"

bool KeyboardDevice::ProcessEvent(void* Event, InputAction& Action)
{
    SDL_Event* event = (SDL_Event*)Event;

    switch(event->type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            InputAction action;
            action.Category = InputCategory::KEYBOARD;
            action.Key = event->key.keysym.scancode;
            action.State = (InputActionState)(event->type - SDL_KEYDOWN);
            Action = action;
            return true;
    };

    return false;
}