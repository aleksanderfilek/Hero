#pragma once

#include"../Core/ISystem.hpp"
#include"../Core/Sid.hpp"
#include"../Core/IResource.hpp"

#include<unordered_map>
#include<vector>
#include<utility>
#include<string>

namespace Hero
{

class Resources : public ISystem
{
private:
  std::unordered_map<Sid, IResource*, SidHashFunction> bank;

  std::unordered_map<int, ResourceFunctions> Functions;

public:
  Resources(const Sid& sid);
  ~Resources();

  void init();
  void update();
  void close();

  template<class T> bool RegisterResource()
  {
    int id = Functions.size();
    ResourceFunctions functions = {T::Load, T::Unload};
    return Functions.insert({T::GetId(), functions}).second;
  }

  bool Exists(const Sid& sid) const;
  IResource* Get(const Sid& sid) const;
  bool Add(const Sid& sid, IResource* resource);
  bool Add(const Sid& sid, int ResourceId, std::string& path);
  void Remove(const Sid& sid);
  bool LoadFromFile(const std::string& path);
  void UnloadFromFile(const std::string& path);
  void Clear();
};

}