#pragma once

#include"../Systems/Resources.hpp"
#include"Shader.hpp"
#include<unordered_map>

/*
file format
resource id
shader id
properties count
property id
data type
data
...
*/
namespace Hero
{

class Material : public ResourceHandle
{
private:
  struct DataPair
  {
    uint8_t id;
    ShaderData value;
    
    DataPair(){}
    ~DataPair(){}
  };

  class Shader* shader;

  std::unordered_map<Sid, DataPair, SidHashFunction> properties;

public:
  HERO Material();
  HERO ~Material();

  HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
  HERO static void Unload(ResourceHandle* resource);
  static int GetId(){ return MATERIAL_ID; }

  HERO void Bind();
};

}