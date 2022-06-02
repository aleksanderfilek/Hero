#pragma once

#include"../Core/IResource.hpp"
#include"../Core/Sid.hpp"
#include<utility>
#include<unordered_map>
#include <cstdint>
#include"../Core/Math.hpp"

namespace Hero
{

class Prefab : public IResource
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

  HERO static IResource* Load(const std::string& path);
  HERO static void Unload(IResource* resource);
  static int GetId(){ return 5; }

  HERO class Actor* Spawn(class ComponentContext* Context, Float3 Position, Float3 Rotation, Float3 Scale);

  HERO void Save(const std::string& path);
};

}