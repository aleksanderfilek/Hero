#ifndef HERO_CORE_H_
#define HERO_CORE_H_

#include<stdint.h>

typedef void* HeroCore;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroCore* heroCoreInit(void);
extern void heroCoreStart(HeroCore* core);
extern void heroCoreClose(HeroCore* core);

extern double heroCoreGetDeltaTime(const HeroCore* core);

extern void heroCoreModuleSetCapacity(HeroCore* core, uint32_t new_capacity);
extern void heroCoreModuleAdd(HeroCore* core, char* name, void* data, 
                                void (*update)(void* data), void (*destroy)(void* ptr));
extern void* heroCoreModuleGet(HeroCore* core, const char* name);
extern void heroCoreModuleRemove(HeroCore* core, const char* name);

#ifdef __cplusplus
}
#endif

#endif