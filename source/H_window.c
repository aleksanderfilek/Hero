#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdint.h>

#include<stdbool.h>

#include"H_math.h"

typedef enum
{
    HERO_WINDOW_CLOSE = 0,
    HERO_WINDOW_COUNT = 1
} HeroWindowEventType;

typedef struct
{
    SDL_Window *sdlWindow;
    SDL_GLContext glContext;
    HeroInt2 size;
    bool fullscreen;

    void (*eventFunc[HERO_WINDOW_COUNT])(void* data);
} HeroWindow;

void heroWindowDestroy(void* ptr);

HeroWindow* heroWindowInit(const char *title, int width, int height, int flags)
{
    // init window
    HeroWindow* window = (HeroWindow*)malloc(sizeof(HeroWindow));
    memset(window, 0, sizeof(HeroWindow));
    
    // Create window object
    window->sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Check if window object was correctly created
    if(window->sdlWindow == NULL){
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        heroWindowDestroy(window);
        return NULL;
    }

    // Set window info data
    window->size = (HeroInt2){ width, height };
    window->fullscreen = false;

    // Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // Create OpenGL context
    window->glContext = SDL_GL_CreateContext(window->sdlWindow);

    glewExperimental = GL_TRUE;
    // Initialize glew
    glewInit();
    // Create viewport
    glViewport(0,0,width, height);
    // Set background color
    glClearColor(1.0f,1.0f,1.0f,1.0f);

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

    // TODO: send fullscreen / resize event
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
    return SDL_GetWindowID(window->sdlWindow);
}

SDL_GLContext heroWindowGetSdlGlContext(HeroWindow* window)
{
    return window->glContext;
}

void heroWindowHandleEvents(HeroWindow* window, SDL_Event* event)
{
    switch( event->window.event )
    {
        case SDL_WINDOWEVENT_CLOSE:
            if(window->eventFunc[HERO_WINDOW_CLOSE] == NULL)
            {
                break;
            }
            window->eventFunc[HERO_WINDOW_CLOSE](window);
            break;
    }
}

void heroWindowSetEvent(HeroWindow* window, HeroWindowEventType event, void (*func)(void* data))
{
    window->eventFunc[event] = func;
}