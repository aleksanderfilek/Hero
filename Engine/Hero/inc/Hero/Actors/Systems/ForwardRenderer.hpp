#pragma once

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include "../../Graphics/Shader.hpp"
#include "../../Graphics/Material.hpp"
#include "../../Graphics/Mesh.hpp"
#include "../../Core/Math.hpp"
#include "../../Graphics/RenderTarget.hpp"
#include"../../Core/Events.hpp"

#include<vector>
#include<utility>

namespace Hero
{

HERO event(ForwardRendererOnResize);

struct MeshGroup
{
  Mesh* mesh = nullptr;
  std::vector<Transform*> transforms;
  std::vector<uint32_t> ids;
  std::vector<bool*> visibility;
};

struct MaterialGroup
{
  Material* material = nullptr;
  std::vector<MeshGroup> groups;
};

class ForwardRenderer : public Actor
{
private:
  bool resize = false;
  Hero::Int2 size;

  RenderTargetConfig config;
  class RenderTarget* renderTarget;
  class Mesh* quad;
  class Shader* shader;

  Material* currentMaterial = nullptr;

  std::vector<MaterialGroup> groups;
  int currentVisibleBudder = 0;

public:
  HERO ForwardRenderer(const Sid& Name);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void Add(Material* material, Mesh* mesh, Transform* transform, uint32_t id, bool* visibility);
  HERO void Remove(Material* material, Mesh* mesh, Transform* transform);
  
  HERO void SetCurrentVisibleBuffer(int Id);

  HERO uint32_t GetIdOnPosition(Int2 Position);

  HERO void Resize(Hero::Int2 Size);
};

}