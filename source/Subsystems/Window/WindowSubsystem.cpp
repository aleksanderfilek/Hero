#include "WindowSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../ThirdParty/SDL2/SDL_opengl.h"
#include "WindowObject.h"
#include "../../Core.h"

WindowSubsystem* WindowSubsystem::instance = nullptr;

WindowSubsystem::WindowSubsystem()
{
    instance = this;
}

void WindowSubsystem::Startup()
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();

    GetSubsystemManager()->GetEvent(inputEventId).AddEvent(this, &WindowSubsystem::HandleEvent);
}

void WindowSubsystem::Shutdown()
{
    for(WindowObject* window: windowObjects)
    {
        delete window;
    }

    SDL_Quit();
}

class WindowObject* WindowSubsystem::CreateWindow(const WindowConfiguration& WindowConfig)
{
    WindowObject* window = new WindowObject(WindowConfig, this);
    windowObjects.Add(window);
    return window;
}

void WindowSubsystem::CloseWindow(class WindowObject* Window)
{
    bool result = windowObjects.Remove(Window);
    if(!result)
    {
        return;
    }

    if(Window->GetId() == 1)
    {
        Core::Get().Stop();
    }

    delete Window;
}

void WindowSubsystem::HandleEvent(void* Data)
{
    SDL_Event* event = (SDL_Event*)Data;

    if(event->type != SDL_WINDOWEVENT)
    {
        return;
    } 

    for(WindowObject* window: windowObjects)
    {
        if(event->window.windowID == window->GetId())
        {
            window->HandleEvent(event);
            return;
        }
    }
}