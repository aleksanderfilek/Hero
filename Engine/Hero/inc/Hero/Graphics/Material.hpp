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

union MaterialData{
  int i;
  float f;
  Float3 vec3;
  Float4 vec4;
  Matrix3x3 mat3;
  Matrix4x4 mat4;
  class Texture* texture;

  MaterialData(){}
  ~MaterialData(){}
};

class Material : public ResourceHandle
{
private:
  struct DataPair
  {
    uint8_t id;
    MaterialData value;
    
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

  HERO void Bind(bool WithShader = true);

  class Shader* GetShader(){ return shader; }
};

}