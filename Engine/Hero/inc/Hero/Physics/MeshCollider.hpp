#pragma once

#include"../Core/Math.hpp"

namespace Hero
{

struct Triangle
{
  Hero::Float3 PointA;
  Hero::Float3 PointB;
  Hero::Float3 PointC;
};

struct MeshCollider
{
  Triangle* Triangles;
  uint32_t Count;
};

}