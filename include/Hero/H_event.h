#ifndef HERO_EVENT_H_
#define HERO_EVENT_H_

#include"H_window.h"

typedef void* HeroEvent;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroEvent* heroEventInit();
extern void heroEventUpdate(void* event);
extern void heroEventDestroy(void* event);
extern void heroEventAddWindow(HeroEvent* event, HeroWindow* window);
extern void heroEventRemoveWindow(HeroEvent* event, HeroWindow* window);

#ifdef __cplusplus
}
#endif

#endif