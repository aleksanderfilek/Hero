#pragma once

#include"../Core/Sid.hpp"

#include<unordered_map>
#include<vector>

namespace Hero
{

class ComponentContext
{
private:
  std::unordered_map<Sid, class IComponentSystemHandle*, SidHashFunction> systems;

public:
  HERO ~ComponentContext();

  HERO void Update();

  HERO void Register(const Sid& sid, IComponentSystemHandle* system);
  HERO void Unregister(const Sid& sid);
  HERO IComponentSystemHandle* Get(const Sid& sid) const;
  HERO void Clear();
};

}