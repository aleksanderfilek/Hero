#pragma once

#include"../Hero/Core/Math.hpp"

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