#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"H_headers.h"
#include"H_math.h"
#include"H_debug.h"
#include"H_color.h"

typedef enum
{
    HERO_WINDOW_SHOWN = 0,
    HERO_WINDOW_HIDDEN = 1,
    HERO_WINDOW_EXPOSED = 2,
    HERO_WINDOW_MOVED = 3,
    HERO_WINDOW_RESIZED = 4,
    HERO_WINDOW_SIZE_CHANGED = 5,
    HERO_WINDOW_MINIMIZED = 6,
    HERO_WINDOW_MAXIMIZED = 7,
    HERO_WINDOW_RESTORED = 8,
    HERO_WINDOW_ENTER = 9,
    HERO_WINDOW_LEAVE = 10,
    HERO_WINDOW_FOCUS_GAINED = 11,
    HERO_WINDOW_FOCUS_LOST = 12,
    HERO_WINDOW_CLOSE = 13,
    HERO_WINDOW_COUNT = 14
} HeroWindowEventType;

typedef struct
{
    SDL_Window *sdlWindow;
    SDL_GLContext glContext;
    uint32_t windowID;
    HeroInt2 size;
    HeroColor backgroundColor;

    bool mouseHover;
    bool focused;
    bool fullscreen;
    bool minimized;
    bool shown;

    void (*eventFunc[HERO_WINDOW_COUNT])(void** data);
} HeroWindow;

void heroWindowDestroy(void* ptr);

HeroWindow* heroWindowInit(const char *title, int width, int height, int flags)
{
  glCheckError();
  
    // init window
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        printf("Window: SDL_Init %s\n", SDL_GetError());
        exit(-1);
    }
glCheckError();
    HeroWindow* window = (HeroWindow*)malloc(sizeof(HeroWindow));
    memset(window, 0, sizeof(HeroWindow));
    
    // Create window object
    window->sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
glCheckError();
    // Check if window object was correctly created
    if(window->sdlWindow == NULL){
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        exit(-1);
    }

    window->windowID = SDL_GetWindowID(window->sdlWindow);

    if(TTF_Init() < 0)
    {
        printf("SDL_ttf could not be initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(-1);
    }

    // Set window info data
    window->size = (HeroInt2){ width, height };
    window->fullscreen = false;

    // Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);
glCheckError();
    // Create OpenGL context
    window->glContext = SDL_GL_CreateContext(window->sdlWindow);
glCheckError();
    glewExperimental = GL_TRUE;
    glCheckError();
    // Initialize glew
    glewInit();
    glCheckError();
    // Create viewport
    glViewport(0,0,width, height);
glCheckError();
     window->shown = true;

    window->backgroundColor = (HeroColor){255,255,255,255};

    return window;
}

void heroWindowDestroy(void* ptr)
{
    HeroWindow* window = (HeroWindow*)ptr;
    SDL_DestroyWindow(window->sdlWindow);
    SDL_GL_DeleteContext(window->glContext);
    free(window);
}

void heroWindowSetFullscreen(HeroWindow* window, bool state)
{
    window->fullscreen = state;
    int flag = (state == true)? SDL_WINDOW_FULLSCREEN : 0;
    SDL_SetWindowFullscreen(window->sdlWindow, flag);
}

bool heroWindowGetFullscreen(HeroWindow* window)
{
    return window->fullscreen;
}

HeroInt2 heroWindowGetSize(HeroWindow* window)
{
    return window->size;
}

SDL_Window* heroWindowGetSdlWindow(HeroWindow* window)
{
    return window->sdlWindow;
}

uint32_t heroWindowGetId(HeroWindow* window)
{
    return window->windowID;
}

SDL_GLContext heroWindowGetSdlGlContext(HeroWindow* window)
{
    return window->glContext;
}

void heroWindowHandleEvents(HeroWindow* window, SDL_Event* event)
{
    if(event->type == SDL_WINDOWEVENT && event->window.windowID == window->windowID)
    {

    void* args[2] = { (void*)window, (void*)&event->window };

    switch( event->window.event )
    {
        case SDL_WINDOWEVENT_SHOWN:
            window->shown = true;
            if(window->eventFunc[HERO_WINDOW_SHOWN])
            {
                window->eventFunc[HERO_WINDOW_SHOWN](args);
            }
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            window->shown = false;
            if(window->eventFunc[HERO_WINDOW_HIDDEN])
            {
                window->eventFunc[HERO_WINDOW_HIDDEN](args);
            }
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            if(window->eventFunc[HERO_WINDOW_EXPOSED])
            {
                window->eventFunc[HERO_WINDOW_EXPOSED](args);
            }
            break;
        case SDL_WINDOWEVENT_MOVED:
            if(window->eventFunc[HERO_WINDOW_MOVED])
            {
                window->eventFunc[HERO_WINDOW_MOVED](args);
            }
            break;
        case SDL_WINDOWEVENT_RESIZED:
            window->size = (HeroInt2){ event->window.data1, event->window.data2 };
            glViewport(0,0,window->size.x, window->size.y);
            if(window->eventFunc[HERO_WINDOW_RESIZED])
            {
                window->eventFunc[HERO_WINDOW_RESIZED](args);
            }
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            window->size = (HeroInt2){ event->window.data1, event->window.data2 };
            glViewport(0,0,window->size.x, window->size.y);
            if(window->eventFunc[HERO_WINDOW_SIZE_CHANGED])
            {
                window->eventFunc[HERO_WINDOW_SIZE_CHANGED](args);
            }
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            window->minimized = true;
            if(window->eventFunc[HERO_WINDOW_MINIMIZED])
            {
                window->eventFunc[HERO_WINDOW_MINIMIZED](args);
            }
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            window->minimized = false;
            if(window->eventFunc[HERO_WINDOW_MAXIMIZED])
            {
                window->eventFunc[HERO_WINDOW_MAXIMIZED](args);
            }
            break;
        case SDL_WINDOWEVENT_RESTORED:
            window->minimized = false;
            if(window->eventFunc[HERO_WINDOW_RESTORED])
            {
                window->eventFunc[HERO_WINDOW_RESTORED](args);
            }
            break;
        case SDL_WINDOWEVENT_ENTER:
            window->mouseHover = true;
            if(window->eventFunc[HERO_WINDOW_ENTER])
            {
                window->eventFunc[HERO_WINDOW_ENTER](args);
            }
            break;
        case SDL_WINDOWEVENT_LEAVE:
            window->mouseHover = false;
            if(window->eventFunc[HERO_WINDOW_LEAVE])
            {
                window->eventFunc[HERO_WINDOW_LEAVE](args);
            }
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            if(window->eventFunc[HERO_WINDOW_FOCUS_GAINED])
            {
                window->eventFunc[HERO_WINDOW_FOCUS_GAINED](args);
            }
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            if(window->eventFunc[HERO_WINDOW_FOCUS_LOST])
            {
                window->eventFunc[HERO_WINDOW_FOCUS_LOST](args);
            }
            break;
        case SDL_WINDOWEVENT_CLOSE:
            if(window->eventFunc[HERO_WINDOW_CLOSE])
            {
                window->eventFunc[HERO_WINDOW_CLOSE](args);
            }
            break;
    }
    }
}

void heroWindowSetEvent(HeroWindow* window, HeroWindowEventType event, void (*func)(void** data))
{
    window->eventFunc[event] = func;
}

void heroWindowSetCurrent(HeroWindow* window)
{
  HeroColor* color = &window->backgroundColor;
  glClearColor((float)color->r/255.0f,(float)color->g/255.0f,(float)color->b/255.0f,(float)color->a/255.0f);
  
  SDL_GL_MakeCurrent(window->sdlWindow, window->glContext);
}

void heroWindowSetBackgroundColor(HeroWindow* window, HeroColor backgroundColor)
{
    window->backgroundColor = backgroundColor;
}

void heroWindowSetTitle(HeroWindow* window, const char* title)
{
   SDL_SetWindowTitle(window->sdlWindow, title); 
}

bool heroWindowIsShown(HeroWindow* window)
{
    return window->shown;
}

bool heroWindowIsMinimized(HeroWindow* window)
{
    return window->minimized;
}

bool heroWindowIsFocused(HeroWindow* window)
{
    return window->focused;
}

bool heroWindowIsMouseHovering(HeroWindow* window)
{
    return window->mouseHover;
}