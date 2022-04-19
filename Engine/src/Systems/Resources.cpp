#include"Resources.hpp"
#include"Shader.hpp"
#include"Mesh.hpp"

namespace Hero
{

Resources::Resources(const Hero::Sid& sid)
  :ISystem(sid)
{
  RegisterResource<Shader>();
  RegisterResource<Mesh>();
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

IResource* Resources::Get(const Sid& sid) const 
{ 
  return bank.at(sid); 
}

bool Resources::Add(const Sid& sid, IResource* resource)
{
  return bank.insert({sid, resource}).second; 
}

bool Resources::Add(const Sid& sid, int ResourceId, std::string& path)
{
  IResource* resource = Functions[ResourceId].Load(path);
  return bank.insert({sid, resource}).second; 
}

void Resources::Remove(const Sid& sid)
{
  auto resource = bank.find(sid);
  if(resource == bank.end())
    return;

  Functions[resource->second->id].Unload(resource->second);
}

bool Resources::LoadFromFile(const std::string& path)
{
  return false;
}

void Resources::UnloadFromFile(const std::string& path)
{

}

void Resources::Clear()
{
  for(std::pair<Sid, IResource*> resource: bank)
  {
    Functions[resource.second->id].Unload(resource.second);
  }
  bank.clear();
}

}