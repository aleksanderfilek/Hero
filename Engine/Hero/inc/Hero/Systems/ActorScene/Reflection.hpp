#pragma once

#include "../../Core/Core.hpp"

#include <unordered_map>
#include "Actor.hpp"

namespace Hero
{

class Reflection
{
private:
    std::unordered_map<Sid, class ICloneable*, SidHashFunction> prototypes;

public:

    HERO ~Reflection();

    template<class T>
    void Add()
    {
        Sid Type = GetType<T>();
        class ICloneable* actor = new T(Type);
        prototypes.insert({Type, actor});
    }

    HERO class ICloneable* Spawn(const Sid& Type);

};

}