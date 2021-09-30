#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#include"H_headers.h"
#include"H_window.h"

typedef struct
{
    SDL_Event sdlEvent;

    HeroWindow** windows;
    uint32_t windowNumber;
} HeroEvent;

HeroEvent* heroEventInit()
{
    HeroEvent* event = (HeroEvent*)malloc(sizeof(HeroEvent));
    memset(event, 0, sizeof(HeroEvent));

    return event;
}

void heroEventUpdate(HeroEvent* event)
{
    while(SDL_PollEvent(&event->sdlEvent) != 0){
        switch (event->sdlEvent.type)
        {
        case SDL_WINDOWEVENT:
            for(int i = 0; i < event->windowNumber; i++)
            {
                if(event->windows[i] == NULL || 
                    heroWindowGetId(event->windows[i]) != event->sdlEvent.window.windowID)
                {
                    continue;
                }

                heroWindowHandleEvents(event->windows[i], &event->sdlEvent);
                break;
            }
            break;
        }
    }
}

void heroEventDestroy(HeroEvent* event)
{
    free(event->windows);
    free(event);
}

void heroEventAddWindow(HeroEvent* event, HeroWindow* window)
{
    event->windowNumber++;
    event->windows = (HeroWindow**)realloc(event->windows, event->windowNumber * sizeof(HeroWindow*));
    event->windows[event->windowNumber - 1] = window;
}

void heroEventRemoveWindow(HeroEvent* event, HeroWindow* window)
{
    for(int i = 0; i < event->windowNumber; i++)
    {
        if(event->windows[i] == window)
        {
            event->windows[i] = NULL;
        }
    }
}