#ifndef HERO_ACTOR_H_
#define HERO_ACTOR_H_

#include"H_math.h"

typedef void* HeroActor2D;

#ifdef __cplusplus
extern "C" {
#endif

extern HeroInt2 heroActor2DGetPosition(const HeroActor2D* actor);
extern void heroActor2DSetPosition(HeroActor2D* actor, HeroInt2 position);
extern HeroInt2 heroActor2DGetSize(const HeroActor2D* actor);
extern void heroActor2DSetSize(HeroActor2D* actor, HeroInt2 size);
extern float heroActor2DGetRotation(const HeroActor2D* actor);
extern void heroActor2DSetRotation(HeroActor2D* actor, float rotation);

#ifdef __cplusplus
}
#endif

#endif