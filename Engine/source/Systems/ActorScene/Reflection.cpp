#include "Reflection.hpp"
#include "Actor.hpp"

namespace Hero
{

HERO Reflection::~Reflection()
{
    // for(auto prototype: prototypes)
    // {
    //     //delete prototype.second;
    // }
}

HERO class Actor* Reflection::Spawn(const Sid& Type)
{
    return prototypes[Type]->Clone();
}

}