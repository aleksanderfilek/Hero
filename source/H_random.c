#include<time.h>
#include<stdlib.h>
#include<stdint.h>

void heroRandomSetSeed(uint32_t seed)
{
    if(seed > 0)
    {
        srand(seed);
        return;
    }

    srand(time(NULL));
}

int heroRandomGetInt(int min, int max)
{
    return rand()%max + min;
}

float heroRandomGetFloat(float min, float max)
{
    return ((float)rand()/(float)(RAND_MAX)) * max + min;
}