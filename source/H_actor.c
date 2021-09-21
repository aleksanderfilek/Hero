#include"H_math.h"

typedef struct
{
    HeroInt2 position;
    HeroInt2 size;
    float rotation;
} HeroActor2D;

HeroInt2 heroActor2DGetPosition(const HeroActor2D* actor)
{
    return actor->position;
}

void heroActor2DSetPosition(HeroActor2D* actor, HeroInt2 position)
{
    actor->position = position;
}

HeroInt2 heroActor2DGetSize(const HeroActor2D* actor)
{
    return actor->size;
}

void heroActor2DSetSize(HeroActor2D* actor, HeroInt2 size)
{
    actor->size = size;
}

float heroActor2DGetRotation(const HeroActor2D* actor)
{
    return actor->rotation;
}

void heroActor2DSetRotation(HeroActor2D* actor, float rotation)
{
    actor->rotation = rotation;
}
