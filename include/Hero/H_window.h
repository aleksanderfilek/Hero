#ifndef HERO_WINDOW_H_
#define HERO_WINDOW_H_

#include<stdbool.h>
#include<stdint.h>

#include"H_headers.h"
#include"H_math.h"
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

typedef void* HeroWindow;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroWindow* heroWindowInit(const char *title, int width, int height, int flags);
extern void heroWindowDestroy(void* ptr);

extern void heroWindowSetFullscreen(HeroWindow* window, bool state);
extern bool heroWindowIsFullscreen(HeroWindow* window);
extern HeroInt2 heroWindowGetSize(HeroWindow* window);
extern SDL_Window* heroWindowGetSdlWindow(HeroWindow* window);
extern uint32_t heroWindowGetId(HeroWindow* window);
extern SDL_GLContext heroWindowGetSdlGlContext(HeroWindow* window);
extern void heroWindowSetCurrentContext(HeroWindow* window);
extern void heroWindowSetBackgroundColor(HeroWindow* window, HeroColor backgroundColor);
extern void heroWindowSetTitle(HeroWindow* window, const char* title);
extern bool heroWindowIsShown(HeroWindow* window);
extern bool heroWindowIsMinimized(HeroWindow* window);
extern bool heroWindowIsFocused(HeroWindow* window);
extern bool heroWindowIsMouseHovering(HeroWindow* window);

extern void heroWindowHandleEvents(HeroWindow* window, SDL_Event* event);
extern void heroWindowSetEvent(HeroWindow* window, HeroWindowEventType event, void (*func)(void** data));

#ifdef __cplusplus
}
#endif

#endif