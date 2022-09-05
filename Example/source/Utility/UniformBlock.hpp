#pragma once

#include "../Hero/Core/Sid.hpp"
#include"../Hero/ThirdParty/GL/Gl.hpp"

#include<unordered_map>

class UniformBlock
{
private:
  uint32_t Id;
  uint32_t Ubo;

  uint32_t Size = 0;
  std::unordered_map<Hero::Sid, uint32_t, Hero::SidHashFunction> OffsetMap;

public:

  template<typename T>
  void Register(const Hero::Sid& Name)
  {
    OffsetMap.insert({Name, Size});
    Size += sizeof(T);
  }

  void Apply(uint32_t NewId);

  template<typename T>
  void Set(const Hero::Sid& Name, T Value)
  {
    if(OffsetMap.find(Name) == OffsetMap.end())
    {
      return;
    }

    uint32_t offset = OffsetMap[Name];
    glBindBuffer(GL_UNIFORM_BUFFER, Ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(T), (void*)&Value);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }
};