#ifndef HERO_FONT_H_
#define HERO_FONT_H_

#include<SDL2/SDL_ttf.h>

typedef TTF_Font H_Font;

#ifdef __cplusplus
extern "C" {
#endif

extern H_Font* H_Font_Load(const char* path, int size);
extern void H_Font_Unload(H_Font* font);

#ifdef __cplusplus
}
#endif

#endif