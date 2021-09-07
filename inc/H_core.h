#ifndef HERO_CORE_H_
#define HERO_CORE_H_

#include<stdint.h>

typedef void* H_Core;

#ifdef __cplusplus
extern "C" {
#endif

extern H_Core* H_Core_init(void);
extern void H_Core_start(H_Core* core);
extern void H_Core_close(H_Core* core);

extern double H_Core_delta_time(const H_Core* core);

extern void H_Core_Module_set_capacity(H_Core* core, uint32_t new_capacity);
extern void H_Core_Module_add(H_Core* core, char* name, void* data, 
                                void (*update)(void* data), void (*destroy)(void* ptr));
extern void* H_Core_Module_get(H_Core* core, const char* name);
extern void H_Core_Module_delete(H_Core* core, const char* name);

#ifdef __cplusplus
}
#endif

#endif