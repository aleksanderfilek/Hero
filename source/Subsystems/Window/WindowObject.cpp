#include "WindowObject.h"

WindowObject::WindowObject(const WindowConfiguration& WindowConfig, WindowSubsystem* WindowSubsystem)
    : configuration(WindowConfig), windowSubsystem(WindowSubsystem)
{
    
    sdlWindow = SDL_CreateWindow(*configuration.Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, configuration.Size.X, configuration.Size.Y, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (!sdlWindow) {
        //std::cout << "[" << getSidString(id) << "] Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    windowId = SDL_GetWindowID(sdlWindow);

    glContext = SDL_GL_CreateContext(sdlWindow);

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer)
    {
        //std::cout << "[" << getSidString(id) << "] Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    glViewport(0, 0, configuration.Size.X, configuration.Size.Y);
}

WindowObject::~WindowObject()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

void WindowObject::Close()
{
    windowSubsystem->CloseWindow(this);
}

void WindowObject::HandleEvent(SDL_Event* Event)
{
    switch (Event->window.event)
    {
    case SDL_WINDOWEVENT_SHOWN:
        shown = true;
        OnWindowEventShown.Broadcast();
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        shown = false;
        OnWindowEventHidden.Broadcast();
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        OnWindowEventExposed.Broadcast();
        break;
    case SDL_WINDOWEVENT_MOVED:
        OnWindowEventMoved.Broadcast();
        break;
    case SDL_WINDOWEVENT_RESIZED: {
        configuration.Size = { Event->window.data1, Event->window.data2 };
        glViewport(0, 0, configuration.Size.X, configuration.Size.Y);
        OnWindowEventResized.Broadcast(configuration.Size);
    } break;
    case SDL_WINDOWEVENT_SIZE_CHANGED: {
        configuration.Size = { Event->window.data1, Event->window.data2 };
        glViewport(0, 0, configuration.Size.X, configuration.Size.Y);
        OnWindowEventSizeChanged.Broadcast(configuration.Size);
    } break;
    case SDL_WINDOWEVENT_MINIMIZED:
        minimized = true;
        OnWindowEventMinimized.Broadcast();
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
        minimized = false;
        OnWindowEventMaximized.Broadcast();
        break;
    case SDL_WINDOWEVENT_RESTORED:
        minimized = false;
        OnWindowEventRestored.Broadcast();
        break;
    case SDL_WINDOWEVENT_ENTER:
        mouseHover = true;
        OnWindowEventEnter.Broadcast();
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseHover = false;
        OnWindowEventLeave.Broadcast();
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        focused = true;
        OnWindowEventFocusGained.Broadcast();
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        focused = false;
        OnWindowEventFocusLost.Broadcast();
        break;
    case SDL_WINDOWEVENT_CLOSE:
        OnWindowEventClose.Broadcast();
        Close();
        break;
    }
}