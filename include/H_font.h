#ifndef HERO_FONT_H_
#define HERO_FONT_H_

#include<SDL2/SDL_ttf.h>

typedef TTF_Font HeroFont;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroFont* heroFontLoad(const char* path, int size);
extern void heroFontUnload(HeroFont* font);

#ifdef __cplusplus
}
#endif

#endif