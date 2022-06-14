#pragma once

#include"../Systems/Resources.hpp"
#include"../Core/Sid.hpp"
#include<utility>
#include<unordered_map>
#include <cstdint>
#include"../Core/Math.hpp"

namespace Hero
{

class Prefab : public ResourceHandle
{
private:
  uint8_t* data = nullptr;
  uint32_t size = 0;
  uint32_t count = 0;
  std::unordered_map<Sid, std::pair<uint8_t*, uint32_t>, SidHashFunction> componentsData;

  Sid name;

public:
  HERO Prefab();
  HERO Prefab(Sid Name, class Actor* RefActor);

  HERO ~Prefab();

  HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
  HERO static void Unload(ResourceHandle* resource);
  static int GetId(){ return PREFAB_ID; }

  HERO class Actor* Spawn(class ComponentContext* Context, Float3 Position, Float3 Rotation, Float3 Scale);

  HERO void Save(const std::string& path);
};

}