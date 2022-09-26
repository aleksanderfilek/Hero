#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Hero/Graphics/Shader.hpp"
#include "../Hero/Graphics/Material.hpp"
#include "../Hero/Graphics/Mesh.hpp"
#include "../Components/Transform.hpp"

#include<vector>
#include<utility>

struct MeshGroup
{
  Hero::Mesh* mesh = nullptr;
  std::vector<std::pair<TransformComponent*, uint32_t>> transforms;
};

struct MaterialGroup
{
  Hero::Material* material = nullptr;
  std::vector<MeshGroup> groups;
};

class Renderer : public Hero::Actor
{
private:
  Hero::Shader* currentShader = nullptr;

  std::vector<MaterialGroup> groups;

public:
  Renderer(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;

  void Register(Hero::Material* material, Hero::Mesh* mesh, TransformComponent* transforms, uint32_t count);
};