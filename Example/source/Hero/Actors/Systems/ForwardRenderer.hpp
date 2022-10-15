#pragma once

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include "../../Graphics/Shader.hpp"
#include "../../Graphics/Material.hpp"
#include "../../Graphics/Mesh.hpp"
#include "../../Core/Math.hpp"

#include<vector>
#include<utility>

namespace Hero
{

struct MeshGroup
{
  Mesh* mesh = nullptr;
  std::vector<Transform*> transforms;
};

struct MaterialGroup
{
  Material* material = nullptr;
  std::vector<MeshGroup> groups;
};

class ForwardRenderer : public Actor
{
private:
  class RenderTarget* renderTarget;
  class Mesh* quad;
  class Shader* shader;

  Material* currentMaterial = nullptr;

  std::vector<MaterialGroup> groups;

public:
  HERO ForwardRenderer(const Sid& NewId);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void Register(Material* material, Mesh* mesh, Transform* transform);
};

}