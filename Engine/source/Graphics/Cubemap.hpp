#pragma once

#include"../Systems/Resources.hpp"
#include"Mesh.hpp"

#include<string>
#include<vector>
#include<cstdlib>

/*
---Format---
Id,
width, 
height,
channel,
size1,
texture1,
size2,
texture2,
size3,
texture3,
size4
texture4
*/

namespace Hero
{

class Cubemap : public Mesh
{
private:
  uint32_t glId;
  
public:
  HERO Cubemap();
  HERO Cubemap(const std::vector<std::string> path);
  HERO ~Cubemap();

  HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
  HERO static void Unload(ResourceHandle* resource);
  static int GetId(){ return CUBEMAP_ID; }

  HERO void draw() override;
};

}