#pragma once

#include"../Core/ISystem.hpp"
#include"../Core/Math.hpp"
#include"../Graphics/Color.hpp"
#include"../Core/Events.hpp"
#include"../ThirdParty/SDL2/SDL.h"
#include"../ThirdParty/GL/Gl.hpp"
#include"../ThirdParty/SDL2/SDL_opengl.h"

#include<cstdint>

namespace Hero
{
namespace System
{

enum class WindowEventType
{
    SHOWN = 0,
    HIDDEN = 1,
    EXPOSED = 2,
    MOVED = 3,
    RESIZED = 4,
    SIZE_CHANGED = 5,
    MINIMIZED = 6,
    MAXIMIZED = 7,
    RESTORED = 8,
    ENTER = 9,
    LEAVE = 10,
    FOCUS_GAINED = 11,
    FOCUS_LOST = 12,
    CLOSE = 13,
    COUNT = 14
};

class Window : public ISystem
{
private:
    uint32_t id;
    Int2 size;
    bool fullScreen;

    SDL_Window* sdlWindow;
    SDL_Renderer* renderer;
    SDL_GLContext glContext;

    Color backgroundColor;
    bool mouseHover;
    bool focused;
    bool fullscreen;
    bool minimized;
    bool shown;

    EventHandler events[(int)WindowEventType::COUNT];

    bool renderFlag = false;

public:
    HERO Window(const Sid& sid, const char *title, int width, int height, int sdlflags = 0);
    HERO ~Window();

    HERO void init();
    HERO void update();
    HERO void close();

    inline SDL_Window* getWindow(){ return sdlWindow; }
    inline SDL_Renderer* getRenderer(){ return renderer; }
    inline SDL_GLContext getGlContext(){ return glContext; }
    inline void setFullscreen(bool state)
    {
        fullscreen = state;
        int flag = (state == true)? SDL_WINDOW_FULLSCREEN : 0;
        SDL_SetWindowFullscreen(sdlWindow, flag);
    }
    inline bool getFullscreen(){ return fullscreen; }
    inline Int2 getSize(){ return size; }
    inline uint32_t getId(){ return id; }
    inline void setCurrentContext(){ SDL_GL_MakeCurrent(sdlWindow, glContext); }
    inline void setBackgroundColor(Color _backgroundColor)
    {
        backgroundColor = _backgroundColor;
        glClearColor((float)backgroundColor.r/255.0f,(float)backgroundColor.g/255.0f,(float)backgroundColor.b/255.0f,(float)backgroundColor.a/255.0f);
    }
    inline void setTitle(const char* title){ SDL_SetWindowTitle(sdlWindow, title); }
    inline bool isShown(){ return shown; }
    inline bool isMinimized(){ return minimized; }
    inline bool isFocused(){ return focused; }
    inline bool isMouseHovering(){ return mouseHover; }

    HERO void apply(); //aktualizuje okno, rozmiar okna, fullscreen

    inline void render(){ renderFlag = true; }
    HERO void handleEvents(SDL_Event* event);
    inline void setEvent(WindowEventType event, EventFunction func){ events[(int)event].add(func); }
    HERO static void clear();
    HERO static void setDepthTest(bool turnOn);
    HERO static bool isDepthTest();
};

}
}