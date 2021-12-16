#ifndef HERO_FONT_H_
#define HERO_FONT_H_

#include"H_headers.h"

typedef TTF_Font HeroFont;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroFont* heroFontLoad(const char* path, int size);
extern void heroFontUnload(void* font);

#ifdef __cplusplus
}
#endif

#endif