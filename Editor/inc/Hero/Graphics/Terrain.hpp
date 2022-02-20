#pragma once

#include<string>

namespace Hero
{

class Mesh;

class Terrain
{
private:
  Mesh* mesh;

public:
  HERO Terrain(const std::string& path, float yScale, float yShift);
  HERO ~Terrain();

  HERO void draw();
};

}