#ifndef HERO_EVENT_H_
#define HERO_EVENT_H_

#include"H_window.h"

typedef void* H_Event;

#ifdef __cplusplus
extern "C" {
#endif

extern H_Event* H_Event_init();
extern void H_Event_update(void* event);
extern void H_Event_destroy(void* event);
extern void H_Event_add_window(H_Event* event, H_Window* window);
extern void H_Event_delete_window(H_Event* event, H_Window* window);

#ifdef __cplusplus
}
#endif

#endif