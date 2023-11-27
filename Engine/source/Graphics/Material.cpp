#include"Material.hpp"
#include"../Utility/ByteOperations.hpp"
#include"../Core/Debug.hpp"

#include<iostream>

namespace Hero
{

HERO Material::Material()
{
}

HERO Material::~Material()
{
}

HERO ResourceHandle* Material::Load(uint8_t* Data, Resources* system)
{
  Material* material = new Material();

  int index = 0;

  uint32_t shaderId = ReadUint32(Data, &index);
  Sid shaderSid(shaderId);
  material->shader = (Shader*)system->Get(shaderSid);

  material->depthTest = ReadUint8(Data, &index);

  uint32_t propertiesCount = ReadUint32(Data, &index);
  for(int i = 0; i < propertiesCount; i++)
  {
    uint32_t propertyId = ReadUint32(Data, &index);
    uint32_t dataType = ReadUint32(Data, &index);
    DataPair property;
    property.id = dataType;
    switch(dataType)
    {
      case 0:
        ReadPtr(Data, &index, (uint8_t*)&property.value.i, sizeof(int));
        break;
      case 1:
        ReadPtr(Data, &index, (uint8_t*)&property.value.f, sizeof(float));
        break;
      case 2:
        ReadPtr(Data, &index, (uint8_t*)&property.value.vec3, sizeof(Float3));
        break;
      case 3:
        ReadPtr(Data, &index, (uint8_t*)&property.value.vec4, sizeof(Float4));
        break;
      case 4:
        ReadPtr(Data, &index, (uint8_t*)&property.value.mat3, sizeof(Matrix3x3));
        break;
      case 5:
        ReadPtr(Data, &index, (uint8_t*)&property.value.mat4, sizeof(Matrix4x4));
        break;
      case 6:
        uint32_t textureId;
        ReadPtr(Data, &index, (uint8_t*)&textureId, sizeof(uint32_t));
        Sid textureSid(textureId);
        property.value.texture = (Texture*)system->Get(textureSid);
        break;
    }

    material->properties.insert({Sid(propertyId), property});
  }

  return material;
}

HERO void Material::Unload(ResourceHandle* resource)
{
  delete resource;
}

HERO void Material::Bind(bool WithShader)
{
  if(WithShader)
  {
    shader->bind();
  }

  if(depthTest) 
    glEnable(GL_DEPTH_TEST);  
  else 
    glDisable(GL_DEPTH_TEST);
  
  for(auto property: properties)
  {
    switch(property.second.id)
    {
      case 0:
        shader->setInt(property.first, property.second.value.i);
        break;
      case 1:
        shader->setFloat(property.first, property.second.value.f);
        break;
      case 2:
        shader->setFloat3(property.first, property.second.value.vec3);
        break;
      case 3:
        shader->setFloat4(property.first, property.second.value.vec4);
        break;
      case 4:
        shader->setMatrix3f(property.first, property.second.value.mat3);
        break;
      case 5:
        shader->setMatrix4f(property.first, property.second.value.mat4);
        break;
      case 6:
        shader->setTexture(property.first, property.second.value.texture);
        break;
    }
  }
}

}