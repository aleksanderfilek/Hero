#ifndef HERO_WINDOW_H_
#define HERO_WINDOW_H_

#include<stdbool.h>
#include<stdint.h>

#include"H_headers.h"
#include"H_math.h"
#include"H_color.h"

typedef enum
{
    HERO_WINDOW_CLOSE = 0,
    HERO_WINDOW_COUNT = 1
} HeroWindowEventType;

typedef void* HeroWindow;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroWindow* heroWindowInit(const char *title, int width, int height, int flags);
extern void heroWindowDestroy(void* ptr);

extern void heroWindowSetFullscreen(HeroWindow* window, bool state);
extern bool heroWindowGetFullscreen(HeroWindow* window);
extern HeroInt2 heroWindowGetSize(HeroWindow* window);
extern SDL_Window* heroWindowGetSdlWindow(HeroWindow* window);
extern uint32_t heroWindowGetId(HeroWindow* window);
extern SDL_GLContext heroWindowGetSdlGlContext(HeroWindow* window);
extern void heroWindowSetCurrent(HeroWindow* window);
extern void heroWindowSetBackgroundColor(HeroWindow* window, HeroColor backgroundColor);

extern void heroWindowHandleEvents(HeroWindow* window, SDL_Event* event);
extern void heroWindowSetEvent(HeroWindow* window, HeroWindowEventType event, void (*func)(void* data));

#ifdef __cplusplus
}
#endif

#endif