#ifndef HERO_INPUT_H_
#define HERO_INPUT_H_

#include<stdbool.h>

#include"H_mouse.h"
#include"H_keycode.h"

typedef void* HeroInput;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroInput* heroInputInit();
extern void heroInputUpdate(void* input);
extern void heroInputDestroy(void* ptr);

extern bool heroInputKeyPressed(const HeroInput* input, HeroKeyCode key);
extern bool heroInputKeyDown(const HeroInput* input, HeroKeyCode key);
extern bool heroInputKeyUp(const HeroInput* input, HeroKeyCode key);

extern bool heroInputMouseButtonPressed(const HeroInput* input, HeroMouseButton button);
extern bool heroInputMouseButtonDown(const HeroInput* input, HeroMouseButton button);
extern bool heroInputMouseButtonUp(const HeroInput* input, HeroMouseButton button);

extern void heroInputGetMousePosition(const HeroInput* input, int *x, int *y);
extern void heroInputSetMousePosition(HeroInput* input, int x, int y);

#ifdef __cplusplus
}
#endif

#endif