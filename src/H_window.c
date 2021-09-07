#include<SDL2/SDL.h>
#include<GL/glew.h>
#include<stdint.h>

#include<stdbool.h>

#include"H_math.h"

typedef enum H_Window_Event_Type
{
    H_WINDOW_CLOSE = 0,
    H_WINDOW_COUNT = 1
} H_Window_Event_Type;

typedef struct
{
    SDL_Window *sdl_window;
    SDL_GLContext gl_context;
    H_int2 size;
    bool full_screen;

    void (*event_func[H_WINDOW_COUNT])(void* data);
} H_Window;

H_Window* H_Window_init(const char *title, int width, int height, int flags)
{
    // init window
    H_Window* window = (H_Window*)malloc(sizeof(H_Window));
    memset(window, 0, sizeof(H_Window));
    
    // Create window object
    window->sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // Check if window object was correctly created
    if(window->sdl_window == NULL){
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        goto error;
    }

    // Set window info data
    window->size = (H_int2){ width, height };
    window->full_screen = false;

    // Setting OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // Create OpenGL context
    window->gl_context = SDL_GL_CreateContext(window->sdl_window);

    glewExperimental = GL_TRUE;
    // Initialize glew
    glewInit();
    // Create viewport
    glViewport(0,0,width, height);
    // Set background color
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    return window;

    // Section with removing data after error;
error:
    SDL_DestroyWindow(window->sdl_window);
    SDL_GL_DeleteContext(window->gl_context);
    free(window);

    return NULL;
}

void H_Window_destroy(void* ptr)
{
    H_Window* window = (H_Window*)ptr;
    SDL_DestroyWindow(window->sdl_window);
    SDL_GL_DeleteContext(window->gl_context);
    free(window);
}

void H_Window_set_fullscreen(H_Window* window, bool state)
{
    window->full_screen = state;

    // TODO: send fullscreen / resize event
}

bool H_Window_get_fullscreen(H_Window* window)
{
    return window->full_screen;
}

H_int2 H_Window_get_size(H_Window* window)
{
    return window->size;
}

SDL_Window* H_Window_get_sdl_window(H_Window* window)
{
    return window->sdl_window;
}

uint32_t H_Window_get_id(H_Window* window)
{
    return SDL_GetWindowID(window->sdl_window);
}

SDL_GLContext H_Window_get_sdl_glcontext(H_Window* window)
{
    return window->gl_context;
}

void H_Window_handle_events(H_Window* window, SDL_Event* event)
{
    switch( event->window.event )
    {
        case SDL_WINDOWEVENT_CLOSE:
            if(window->event_func[H_WINDOW_CLOSE] == NULL)
            {
                break;
            }
            window->event_func[H_WINDOW_CLOSE](window);
            break;
    }
}

void H_Window_set_event(H_Window* window, H_Window_Event_Type event, void (*func)(void* data))
{
    window->event_func[event] = func;
}