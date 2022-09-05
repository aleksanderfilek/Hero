#pragma once

#include "../Hero/Core/Sid.hpp"
#include<unordered_map>

class UniformBuffer
{
private:
  uint32_t Id;
  uint32_t Ubo;

  uint32_t Size = 0;
  std::unordered_map<Sid, std::pair<uint32_t, uint32_t>, SidHashFunction> OffsetMap;

public:
  UniformBuffer(uint32_t NewId);

  template<typename T>
  void Register(const Hero::Sid& Name)
  {
    std::pair<uint32_t,uint32_t> variable(Name, Size);
    OffsetMap.insert(variable);
    Size += sizeof(T);
  }

  void Apply();

  template<typename T>
  void Set(Sid Name, T Value)
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