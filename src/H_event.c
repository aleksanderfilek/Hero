#include<SDL2/SDL.h>
#include<stdlib.h>
#include<stdint.h>

#include"H_window.h"

typedef struct
{
    SDL_Event sdl_event;

    H_Window** windows;
    uint32_t window_number;
} H_Event;

H_Event* H_Event_init()
{
    H_Event* event = (H_Event*)malloc(sizeof(H_Event));
    memset(event, 0, sizeof(H_Event));

    return event;
}

void H_Event_update(H_Event* event)
{
    while(SDL_PollEvent(&event->sdl_event) != 0){
        switch (event->sdl_event.type)
        {
        case SDL_WINDOWEVENT:
            for(int i = 0; i < event->window_number; i++)
            {
                if(event->windows[i] == NULL || 
                    H_Window_get_id(event->windows[i]) != event->sdl_event.window.windowID)
                {
                    continue;
                }

                H_Window_handle_events(event->windows[i], &event->sdl_event);
                break;
            }
            break;
        }
    }
}

void H_Event_destroy(H_Event* event)
{
    free(event->windows);
    free(event);
}

void H_Event_add_window(H_Event* event, H_Window* window)
{
    event->window_number++;
    event->windows = (H_Window**)realloc(event->windows, event->window_number * sizeof(H_Window*));
    event->windows[event->window_number - 1] = window;
}

void H_Event_delete_window(H_Event* event, H_Window* window)
{
    for(int i = 0; i < event->window_number; i++)
    {
        if(event->windows[i] == window)
        {
            event->windows[i] = NULL;
        }
    }
}