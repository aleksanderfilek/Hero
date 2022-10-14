#pragma once

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include "../../Graphics/Mesh.hpp"
#include"../../Components/Transform.hpp"
#include "../../Graphics/Material.hpp"
#include "../Systems/ForwardRenderer.hpp"

#include<vector>

namespace Hero
{

class StaticMesh : public Actor
{
private:
  ForwardRenderer* renderer;
  Mesh* mesh;
  Material* material;

  std::vector<TransformComponent> transforms;

public:
  HERO StaticMesh(const Sid& NewId);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void SetMesh(Mesh* Mesh);
  HERO void SetMaterial(Material* Material);

  HERO void AddInstance(TransformComponent& transform);
  HERO void UpdateInstance(TransformComponent& transform, int Index);
};

}