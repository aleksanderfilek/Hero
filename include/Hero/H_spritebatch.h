#ifndef HERO_SPRITEBATCH_H_
#define HERO_SPRITEBATCH_H_

#include<stdint.h>

#include"H_texture.h"
#include"H_math.h"
#include"H_color.h"
#include"H_shader.h"
#include"H_window.h"

typedef void* HeroSpriteBatch;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroSpriteBatch* heroSpriteBatchInit(HeroWindow* window, uint32_t capacity, uint32_t maxTextures, const HeroShader* shader);
extern void heroSpriteBatchDestroy(HeroSpriteBatch* spriteBatch);
extern void heroSpriteBatchBegin(HeroSpriteBatch* spriteBatch);
extern void heroSpriteBatchEnd(HeroSpriteBatch* spriteBatch);
extern void heroSpriteBatchDrawTexture(HeroSpriteBatch* spriteBatch, const HeroTexture* texture, const HeroInt2 position, const HeroInt2 size);
extern void heroSpriteBatchDrawTextureEx(HeroSpriteBatch* spriteBatch, const HeroTexture* texture, const HeroInt2 position, const HeroInt2 size, const HeroInt4 rect, float angle, HeroColor color);

#ifdef __cplusplus
}
#endif

#endif