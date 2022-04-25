#pragma once

#include<string>

namespace Hero
{

class IResource
{
public:
  int id;
};

struct ResourceFunctions
{
  IResource* (*Load)(const std::string& path);
  void (*Unload)(IResource* Resource);
};

template<class T> 
T* LoadResource(const std::string& path)
{
  return (T*)T::Load(path);
}

template<class T>
void UnloadResource(IResource* Resource)
{
  T::Unload(Resource);
}

}