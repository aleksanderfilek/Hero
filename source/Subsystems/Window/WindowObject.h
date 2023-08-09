#pragma once

#include "../../Definitions.h"
#include "WindowSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../ThirdParty/SDL2/SDL_opengl.h"
#include "../../GenericTypes/Event.h"

EVENT_DISPATCHER(WindowEventShown)
EVENT_DISPATCHER(WindowEventHidden)
EVENT_DISPATCHER(WindowEventExposed)
EVENT_DISPATCHER(WindowEventMoved)
EVENT_DISPATCHER(WindowEventResized, Int2)
EVENT_DISPATCHER(WindowEventSizeChanged, Int2)
EVENT_DISPATCHER(WindowEventMinimized)
EVENT_DISPATCHER(WindowEventMaximized)
EVENT_DISPATCHER(WindowEventRestored)
EVENT_DISPATCHER(WindowEventEnter)
EVENT_DISPATCHER(WindowEventLeave)
EVENT_DISPATCHER(WindowEventFocusGained)
EVENT_DISPATCHER(WindowEventFocusLost)
EVENT_DISPATCHER(WindowEventClose)

class HERO_API WindowObject
{
private:
    WindowConfiguration configuration;
    WindowSubsystem* windowSubsystem;

    uint32_t windowId = 0;
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_GLContext glContext;

    bool mouseHover = false;
    bool focused = true;
    bool fullscreen = false;
    bool minimized = false;
    bool shown = true;

public:
    WindowObject(const WindowConfiguration& WindowConfig, WindowSubsystem* WindowSubsystem);
    ~WindowObject();

    void Close();

    WindowConfiguration& GetConfiguration() { return configuration; }
    uint32_t GetId() const { return windowId; }

    bool IsShown() const { return shown; }
    bool IsMinimized() const { return minimized; }
    bool IsFocused() const { return focused; }
    bool IsMouseHovering() const { return mouseHover; }

    void HandleEvent(SDL_Event* Event);

    WindowEventShown OnWindowEventShown;
    WindowEventHidden OnWindowEventHidden;
    WindowEventExposed OnWindowEventExposed;
    WindowEventMoved OnWindowEventMoved;
    WindowEventResized OnWindowEventResized;
    WindowEventSizeChanged OnWindowEventSizeChanged;
    WindowEventMinimized OnWindowEventMinimized;
    WindowEventMaximized OnWindowEventMaximized;
    WindowEventRestored OnWindowEventRestored;
    WindowEventEnter OnWindowEventEnter;
    WindowEventLeave OnWindowEventLeave;
    WindowEventFocusGained OnWindowEventFocusGained;
    WindowEventFocusLost OnWindowEventFocusLost;
    WindowEventClose OnWindowEventClose;
};