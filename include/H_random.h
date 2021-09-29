#ifndef HERO_RANDOM_H_
#define HERO_RANDOM_H_

#include<stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void heroRandomSetSeed(uint32_t seed);
extern int heroRandomGetInt(int min, int max);
extern int heroRandomGetFloat(float min, float max);

#ifdef __cplusplus
}
#endif

#endif