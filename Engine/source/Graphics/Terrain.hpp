#pragma once

#include"../Systems/Resources.hpp"
#include"Mesh.hpp"

/*
resourceId
width
height
iamgeSize
image
yScale
yShift
*/

namespace Hero
{

class Terrain : public Mesh
{
private:

public:
  HERO Terrain();
  //HERO Terrain(float yScale, float yShift);
  HERO ~Terrain();

  HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
  HERO static void Unload(ResourceHandle* resource);
  static int GetId(){ return TERRAIN_ID; }
};

}