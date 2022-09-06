#pragma once

#include"../Core/ISystem.hpp"
#include"../Core/Sid.hpp"

#include<unordered_map>
#include<vector>
#include<utility>
#include<string>

#define MESH_ID         1
#define SHADER_ID       2
#define TEXTURE_ID      3
#define SPRITESHEET_ID  4
#define TERRAIN_ID      5
#define MATERIAL_ID     7
#define CUBEMAP_ID      8
#define FONT_ID         9

namespace Hero
{

class ResourceHandle
{
public:
  int id; 
};

class Resources;

struct ResourceFunctions
{
  ResourceHandle* (*Load)(uint8_t* Data, Resources* system);
  void (*Unload)(ResourceHandle* Resource);
};

class Resources : public ISystem
{
private:
  std::unordered_map<Sid, ResourceHandle*, SidHashFunction> bank;

  std::unordered_map<int, ResourceFunctions> Functions;

public:
  HERO Resources(const Sid& sid);
  HERO ~Resources();

  HERO void init();
  HERO void update();
  HERO void close();

  template<class T> bool RegisterResource()
  {
    int id = Functions.size();
    ResourceFunctions functions = {T::Load, T::Unload};
    return Functions.insert({T::GetId(), functions}).second;
  }

  HERO bool Exists(const Sid& sid) const;
  HERO ResourceHandle* Get(const Sid& sid) const;
  HERO bool Add(const Sid& sid, std::string& path);
  HERO void Remove(const Sid& sid);
  HERO void Clear();
};

}