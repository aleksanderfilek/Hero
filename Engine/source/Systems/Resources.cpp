#include"Resources.hpp"
#include"../Graphics/Shader.hpp"
#include"../Graphics/Mesh.hpp"
#include"../Graphics/Texture.hpp"
#include"../Graphics/Spritesheet.hpp"

#include<fstream>
#include<cstdlib>

namespace Hero
{

Resources::Resources(const Hero::Sid& sid)
  :ISystem(sid)
{
  RegisterResource<Shader>();
  RegisterResource<Mesh>();
  RegisterResource<Texture>();
  RegisterResource<Spritesheet>();
}

Resources::~Resources()
{

}

void Resources::init()
{
  ISystem::init();
}

void Resources::update()
{

}

void Resources::close()
{
  ISystem::close();
}

bool Resources::Exists(const Sid& sid) const 
{ 
  return (bank.find(sid) != bank.end()); 
}

ResourceHandle* Resources::Get(const Sid& sid) const 
{ 
  return bank.at(sid); 
}


bool Resources::Add(const Sid& sid, std::string& path)
{
  std::ifstream file(path, std::ios::binary);
  if(!file.is_open())
  {
    printMessage("Could not load resource");
    return false;
  }

  file.seekg(0, std::ios::end);
  int size = file.tellg();

  int id = 0;
  file.read((char*)&resourceId, sizeof(int)); 
  size -= sizeof(int);

  uint8_t* data = new uint8_t[size];
  file.read((char*)data, size * sizeof(uint8_t));
  file.close();

  ResourceHandle* resource = Functions[resourceId].Load(data);
  delete[] data;
  return bank.insert({Sid(id), reresource}).second; 
}

void Resources::Remove(const Sid& sid)
{
  auto resource = bank.find(sid);
  if(resource == bank.end())
    return;

  Functions[resource->second->GetId()].Unload(resource->second);
}

void Resources::Clear()
{
  for(std::pair<Sid, ResourceHandle*> resource: bank)
  {
    Functions[resource.second->GetId()].Unload(resource.second);
  }
  bank.clear();
}

}