#pragma once

#include "../Core/Sid.hpp"
#include"../ThirdParty/GL/Gl.hpp"

#include<unordered_map>
#include<iostream>

namespace Hero
{

class UniformBlock
{
private:
  uint32_t Id;
  uint32_t Ubo;

  uint32_t Size = 0;
  std::unordered_map<Sid, uint32_t, SidHashFunction> OffsetMap;

public:

  template<typename T>
  void Register(const Sid& Name)
  {
    OffsetMap.insert({Name, Size});
    int size = sizeof(T);
    int bytes = (size / 16) * 16;
    bytes += (size%16 > 0)? 16 : 0;
    Size += bytes;
  }

  void Apply(uint32_t NewId);

  template<typename T>
  void Set(const Sid& Name, T Value)
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

}