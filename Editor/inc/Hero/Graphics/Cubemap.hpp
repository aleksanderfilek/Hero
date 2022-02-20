#pragma once

#include<string>
#include<vector>
#include<cstdlib>
#include"Mesh.hpp"

namespace Hero
{

class Cubemap
{
private:
  uint32_t glId;
  Mesh* mesh;
  
public:
  HERO Cubemap(const std::vector<std::string> path);
  HERO ~Cubemap();

  HERO void draw();
};

}