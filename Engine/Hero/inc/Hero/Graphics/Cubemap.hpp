#pragma once

#include<string>
#include<vector>
#include<cstdlib>

namespace Hero
{

class Cubemap
{
private:
  uint32_t glId;
  class Mesh* mesh;
  
public:
  HERO Cubemap(const std::vector<std::string> path);
  HERO ~Cubemap();

  HERO void draw();
};

}