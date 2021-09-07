#ifndef HERO_TEXTURE_H_
#define HERO_TEXTURE_H_

#include<stdint.h>

#include"H_math.h"
#include"H_color.h"
#include"H_font.h"

typedef enum 
{
    HERO_TEXTUREFLAG_NEAREST = 0,
    HERO_TEXTUREFLAG_LINEAR = 1,
    HERO_TEXTUREFLAG_NO_MIPMAP = 0,
    HERO_TEXTUREFLAG_MIPMAP =  128       
} HeroTextureFlag;

typedef void* HeroTexture;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroTexture* heroLoadTexture(const char* path, uint8_t textureFlags);
extern void heroUnloadTexture(HeroTexture* texture);
extern void heroBindTexture(const HeroTexture* texture);
extern void heroUnbindTexture();
extern HeroTexture* heroTextureFromText(const char* text, HeroColor* color, HeroFont* font, uint8_t textureFlags);

#ifdef __cplusplus
}
#endif

#endif