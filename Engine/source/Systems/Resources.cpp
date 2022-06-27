#include"Resources.hpp"
#include"../Graphics/Shader.hpp"
#include"../Graphics/Mesh.hpp"
#include"../Graphics/Texture.hpp"
#include"../Graphics/Spritesheet.hpp"
#include"../Graphics/Terrain.hpp"
#include"../Components/Prefab.hpp"
#include"../Graphics/Material.hpp"
#include"../Graphics/Cubemap.hpp"
#include"../Graphics/Font.hpp"

#include<fstream>
#include<cstdlib>

namespace Hero
{

HERO Resources::Resources(const Hero::Sid& sid)
  :ISystem(sid)
{
  RegisterResource<Mesh>();
  RegisterResource<Shader>();
  RegisterResource<Texture>();
  RegisterResource<Spritesheet>();
  RegisterResource<Terrain>();
  RegisterResource<Prefab>();
  RegisterResource<Material>();
  RegisterResource<Cubemap>();
  RegisterResource<Font>();
}

HERO Resources::~Resources()
{

}

HERO void Resources::init()
{
  ISystem::init();
}

HERO void Resources::update()
{

}

HERO void Resources::close()
{
  ISystem::close();
}

HERO bool Resources::Exists(const Sid& sid) const 
{ 
  return (bank.find(sid) != bank.end()); 
}

HERO ResourceHandle* Resources::Get(const Sid& sid) const 
{ 
  return bank.at(sid); 
}


HERO bool Resources::Add(const Sid& sid, std::string& path)
{
  std::ifstream file(path, std::ios::binary);
  if(!file.is_open())
  {
    printMessage("Could not load resource");
    return false;
  }

  file.seekg(0, std::ios::end);
  int size = file.tellg();

  int resourceId = 0;
  file.read((char*)&resourceId, sizeof(int)); 
  size -= sizeof(int);

  uint8_t* data = new uint8_t[size];
  file.read((char*)data, size * sizeof(uint8_t));
  file.close();

  ResourceHandle* resource = Functions[resourceId].Load(data, this);
  resource->id = resourceId;
  delete[] data;
  return bank.insert(std::pair<Sid, ResourceHandle*>(Sid(resourceId), resource)).second; 
}

HERO void Resources::Remove(const Sid& sid)
{
  auto resource = bank.find(sid);
  if(resource == bank.end())
    return;

  Functions[resource->second->id].Unload(resource->second);
}

HERO void Resources::Clear()
{
  for(auto resource: bank)
  {
    Functions[resource.second->id].Unload(resource.second);
  }
  bank.clear();
}

}