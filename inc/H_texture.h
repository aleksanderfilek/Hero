#ifndef HERO_TEXTURE_H_
#define HERO_TEXTURE_H_

#include<stdint.h>

#include"H_math.h"
#include"H_color.h"
#include"H_font.h"

typedef enum 
{
    H_TEXTUREFLAG_NEAREST = 0,
    H_TEXTUREFLAG_LINEAR = 1,
    H_TEXTUREFLAG_NO_MIPMAP = 0,
    H_TEXTUREFLAG_MIPMAP =  128       
} H_TextureFlag;

typedef void* H_Texture;

#ifdef __cplusplus
extern "C" {
#endif

extern H_Texture* H_LoadTexture(const char* path, uint8_t textureFlags);
extern void H_UnloadTexture(H_Texture* texture);
extern void H_BindTexture(const H_Texture* texture);
extern void H_UnbindTexture();
extern H_Texture* H_TextureFromText(const char* text, H_Color* color, H_Font* font, uint8_t textureFlags);

#ifdef __cplusplus
}
#endif

#endif