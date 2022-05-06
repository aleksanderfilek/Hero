#include"Random.hpp"

#include<cstdlib>
#include<ctime>

namespace Hero
{

HERO void randomSetSeed(int seed)
{
    if(seed > 0)
    {
        srand(seed);
        return;
    }

    srand(time(NULL));
}

HERO int randomGetInt(int min, int max)
{
    return rand()%max + min;
}

HERO float randomGetFloat(float min, float max)
{
    return ((float)rand()/(float)(RAND_MAX)) * max + min;
}

}