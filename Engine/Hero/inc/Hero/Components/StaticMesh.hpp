#pragma once

#include "../Core/Sid.hpp"
#include"../Systems/ActorScene/ActorComponent.hpp"

#include<vector>

namespace Hero
{

class StaticMesh : public ActorComponent
{
private:
  class ForwardRenderer* renderer;
  class Mesh* mesh;
  class Material* material;
  bool visible = true;

public:
  HERO StaticMesh();

  HERO void Start() override;

  HERO void SetMesh(class Mesh* Mesh);
  HERO void SetMaterial(class Material* Material);
  HERO void SetVisibility(bool Visible);
};

}