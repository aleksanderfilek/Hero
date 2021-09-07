#ifndef HERO_WINDOW_H_
#define HERO_WINDOW_H_

#include<SDL2/SDL.h>
#include<stdbool.h>
#include<stdint.h>

#include"H_math.h"

typedef enum H_Window_Event_Type
{
    H_WINDOW_CLOSE = 0,
    H_WINDOW_COUNT
} H_Window_Event_Type;

typedef void* H_Window;

#ifdef __cplusplus
extern "C" {
#endif

extern H_Window* H_Window_init(const char *title, int width, int height, int flags);
extern void H_Window_destroy(void* ptr);

extern void H_Window_set_fullscreen(H_Window* window, bool state);
extern bool H_Window_get_fullscreen(H_Window* window);
extern H_int2 H_Window_get_size(H_Window* window);
extern SDL_Window* H_Window_get_sdl_window(H_Window* window);
extern uint32_t H_Window_get_id(H_Window* window);
extern SDL_GLContext H_Window_get_sdl_glcontext(H_Window* window);

extern void H_Window_handle_events(H_Window* window, SDL_Event* event);
extern void H_Window_set_event(H_Window* window, H_Window_Event_Type event, void (*func)(void* data));

#ifdef __cplusplus
}
#endif

#endif