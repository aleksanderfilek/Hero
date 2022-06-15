#include"Material.hpp"
#include"../Utility/ByteOperations.hpp"

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
  Shader* shader = (Shader*)system->Get(shaderSid);

  uint32_t propertiesCount = ReadUint32(Data, &index);
  for(int i = 0; i < propertiesCount; i++)
  {
    uint32_t propertyId = ReadUint32(Data, &index);
    uint8_t dataType = ReadUint8(Data, &index);
    DataPair property;
    property.id = dataType;
    switch(dataType)
    {
      case 0:
        ReadPtr(Data, &index, (void*)&property.value.i, sizeof(int));
        break;
      case 1:
        ReadPtr(Data, &index, (void*)&property.value.f, sizeof(float));
        break;
      case 2:
        ReadPtr(Data, &index, (void*)&property.value.vec, sizeof(Float3));
        break;
      case 3:
        ReadPtr(Data, &index, (void*)&property.value.mat4, sizeof(Matrix4x4));
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

HERO void Material::Bind()
{
  shader->bind();
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
        shader->setFloat3(property.first, property.second.value.vec);
        break;
      case 3:
        shader->setMatrix4f(property.first, property.second.value.mat4);
        break;
    }
  }
}

}