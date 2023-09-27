#pragma once

#include "../../Definitions.h"
#include "WindowSubsystem.h"
#include "../../ThirdParty/SDL2/SDL.h"
#include "../../ThirdParty/GL/Gl.h"
#include "../../ThirdParty/SDL2/SDL_opengl.h"
#include "../../GenericTypes/Event.h"
#include "../../Containers/Array.h"

EVENT_DISPATCHER(WindowEventShown, class WindowObject*)
EVENT_DISPATCHER(WindowEventHidden, class WindowObject*)
EVENT_DISPATCHER(WindowEventExposed, class WindowObject*)
EVENT_DISPATCHER(WindowEventMoved, class WindowObject*)
EVENT_DISPATCHER(WindowEventResized, class WindowObject*, Int2)
EVENT_DISPATCHER(WindowEventSizeChanged, class WindowObject*, Int2)
EVENT_DISPATCHER(WindowEventMinimized, class WindowObject*)
EVENT_DISPATCHER(WindowEventMaximized, class WindowObject*)
EVENT_DISPATCHER(WindowEventRestored, class WindowObject*)
EVENT_DISPATCHER(WindowEventEnter, class WindowObject*)
EVENT_DISPATCHER(WindowEventLeave, class WindowObject*)
EVENT_DISPATCHER(WindowEventFocusGained, class WindowObject*)
EVENT_DISPATCHER(WindowEventFocusLost, class WindowObject*)
EVENT_DISPATCHER(WindowEventClose, class WindowObject*)
EVENT_DISPATCHER(WindowEventCustom, const void*)

class WindowRenderTarget
{
public:
    StringId Id;
    class RenderTarget* RenderTarget = nullptr;
};

class HERO_API WindowObject
{
private:
    StringId id;

    WindowConfiguration configuration;
    class WindowSubsystem* windowSubsystem;

    uint32_t windowId = 0;
	SDL_Window* sdlWindow = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_GLContext glContext;
    void ResizeRenderTarget(const Int2& Size);

    bool mouseHover = false;
    bool focused = true;
    bool fullscreen = false;
    bool minimized = false;
    bool shown = true;

public:
    WindowObject(const StringId& Id, const WindowConfiguration& WindowConfig, class WindowSubsystem* WindowSubsystem);
    ~WindowObject();

    void Close();

    class WindowSubsystem* GetWindowSubsystem() const { return windowSubsystem; }
    StringId GetId() const { return id; }
    WindowConfiguration& GetConfiguration() { return configuration; }
    uint32_t GetIdentifier() const { return windowId; }

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
    WindowEventCustom OnWindowEventCustom;

private:
    class RenderTarget* combinedRenderTarget = nullptr;
    Array<WindowRenderTarget> renderTargets;

public:
    WindowRenderTarget* CreateWindowRenderTarget(const StringId& Id);
    WindowRenderTarget* GetWindowRenderTarget(const StringId& Id);
    void RemoveWindowRenderTarget(const StringId& Id);
    void SetWindowRenderTargetOrder(const Array<StringId>& OrderIds);

    void Render();
};