#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Hero/Graphics/Shader.hpp"
#include "../Hero/Graphics/Mesh.hpp"
#include "../Hero/Graphics/Texture.hpp"
#include"../Components/Transform.hpp"
#include "../Hero/Graphics/Material.hpp"

#include<vector>

class StaticMesh : public Hero::Actor
{
private:
  class Renderer* rendererRefs;
  Hero::Mesh* mesh;
  Hero::Material* material;

  TransformComponent *transforms;
  uint32_t count = 0;

public:
  StaticMesh(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;

  void SetRenderer(class Renderer* renderer);
  void SetMesh(Hero::Mesh* Mesh);
  void SetMaterial(Hero::Material* Material);

  void Load(const char* path);
};