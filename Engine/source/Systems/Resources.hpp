#pragma once

#include"../Core/ISystem.hpp"
#include"../Core/Sid.hpp"

#include<unordered_map>
#include<vector>
#include<utility>
#include<string>

namespace Hero
{

class ResourceHandle{};

struct ResourceFunctions
{
  ResourceHandle* (*Load)(uint8_t* Data);
  void (*Unload)(ResourceHandle* Resource);
};

class Resources : public ISystem
{
private:
  std::unordered_map<Sid, ResourceHandle*, SidHashFunction> bank;

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
  ResourceHandle* Get(const Sid& sid) const;
  bool Add(const Sid& sid, std::string& path);
  void Remove(const Sid& sid);
  void Clear();
};

}