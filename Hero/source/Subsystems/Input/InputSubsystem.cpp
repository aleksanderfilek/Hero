#include "InputSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../Core.h"
#include "ControlMap.h"
#include "ControlScheme.h"
#include "Devices/IInputDevice.h"
#include "Devices/KeyboardDevice.h"
#include "Devices/MouseDevice.h"

InputSubsystem* InputSubsystem::instance = nullptr;

InputSubsystem::InputSubsystem()
{
    instance = this;
    updateEnabled = true;
}

void InputSubsystem::Startup()
{
    Subsystem::Startup();

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    {
        exit(-1);
    }

    devices.Add(new KeyboardDevice());
    devices.Add(new MouseDevice());
}

void InputSubsystem::Shutdown()
{
    Subsystem::Shutdown();

    for(IInputDevice* device: devices)
    {
        delete device;
    }

    SDL_Quit();
}

void InputSubsystem::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            Core::Get().Stop();
            return;
        }

        for(IInputDevice* device: devices)
        {
            InputAction action;
            if(device->ProcessEvent(&event, action))
            {
                if(!controlMap)
                    break;

                StringId actionId = controlMap->GetId(action);
                for(int i = controlSchemes.Length() - 1; i >= 0; i--)
                {
                    if(controlSchemes[i]->ProcessAction(actionId, action))
                    {
                        break;
                    }
                }
                break;
            }
        }

        GetSubsystemManager()->BroadcastEvent(inputEventId, &event);
    }
}

IInputDevice* InputSubsystem::GetDevice(StringId Id)
{
    for(IInputDevice* device: devices)
    {
        if(device->GetId() == Id)
        {
            return device;
        }
    }
    return nullptr;
}

void InputSubsystem::SetContolMap(class ControlMap* ControlMap)
{
    controlMap = ControlMap;
}

void InputSubsystem::PushContext(class ControlScheme* Scheme)
{
    controlSchemes.Add(Scheme);
}

class ControlScheme* InputSubsystem::PopContext()
{
    if(controlSchemes.Length() == 0)
    {
        return nullptr;
    }

    class ControlScheme* lastScheme = controlSchemes[controlSchemes.Length() - 1];
    controlSchemes.RemoveAt(controlSchemes.Length() - 1);
    return lastScheme;
}

void InputSubsystem::ToggleCursor(bool Show)
{
    showCursor = Show;
    SDL_ShowCursor(showCursor);
}

bool InputSubsystem::IsCursorVisible() const
{
    return showCursor;
}