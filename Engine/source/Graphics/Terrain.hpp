#pragma once

#include"../Systems/Resources.hpp"

namespace Hero
{

class Terrain : public ResourceHandle
{
private:
  class Mesh* mesh;

public:
  HERO Terrain();
  //HERO Terrain(float yScale, float yShift);
  HERO ~Terrain();

  HERO static ResourceHandle* Load(uint8_t* Data, Resources* system);
  HERO static void Unload(ResourceHandle* resource);
  static int GetId(){ return TERRAIN_ID; }

  HERO void draw();
};

}