#include "MouseDevice.h"
#include "../../../ThirdParty/SDL2/SDL.h"

bool MouseDevice::ProcessEvent(void* Event, InputAction& Action)
{
    SDL_Event* event = (SDL_Event*)Event;

    switch(event->type)
    {
        case SDL_MOUSEMOTION:
            {
                Int2 position = {event->motion.x, event->motion.y};
                Int2 motionVector = {event->motion.xrel, event->motion.yrel};
                OnMouseMotion.Broadcast(position, motionVector);
                return true;
            }break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            {
                InputAction action;
                action.Category = InputCategory::MOUSE;
                action.Key = event->button.button;
                action.State = (InputActionState)(event->type - SDL_MOUSEBUTTONDOWN);
                Action = action;
                return true;
            }break;
        case SDL_MOUSEWHEEL:
            {
                float y = event->wheel.preciseY;
                OnMouseWheelEvent.Broadcast(y);
                return true;
            }break;
    };

    return false;
}