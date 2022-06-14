#include"Terrain.hpp"
#include"Mesh.hpp"
#include"../ThirdParty/Stb/stb_image.h"

#include<vector>
#include<cstring>

namespace Hero
{

HERO Terrain::Terrain()
{

}

HERO Terrain::~Terrain()
{

}

HERO ResourceHandle* Terrain::Load(uint8_t* Data, Resources* system)
{
  return nullptr;
}

HERO void Terrain::Unload(ResourceHandle* resource)
{

}

HERO void Terrain::draw()
{
  mesh->draw();
}

}