#include"Random.hpp"

#include<cstdlib>
#include<ctime>

namespace Hero
{

void randomSetSeed(int seed)
{
    if(seed > 0)
    {
        srand(seed);
        return;
    }

    srand(time(NULL));
}

int randomGetInt(int min, int max)
{
    return rand()%max + min;
}

float randomGetFloat(float min, float max)
{
    return ((float)rand()/(float)(RAND_MAX)) * max + min;
}

}