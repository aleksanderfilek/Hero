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

extern HeroTexture* heroTextureLoad(const char* path, uint8_t textureFlags);
extern void heroTextureUnload(HeroTexture* texture);
extern void heroTextureBind(const HeroTexture* texture);
extern void heroTextureUnbind();
extern HeroTexture* heroTextureFromText(const char* text, HeroColor* color, HeroFont* font, uint8_t textureFlags);
extern HeroTexture* heroTextureConstruct(const char* name, HeroInt2 size, uint32_t glID);
extern uint32_t heroTextureGetGlID(const HeroTexture* texture);
extern HeroInt2 heroTextureGetSize(const HeroTexture* texture);

#ifdef __cplusplus
}
#endif

#endif