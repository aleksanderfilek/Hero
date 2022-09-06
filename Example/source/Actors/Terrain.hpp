#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Hero/Graphics/Shader.hpp"
#include "../Hero/Graphics/Mesh.hpp"
#include "../Components/Transform.hpp"

class Terrain : public Hero::Actor
{
private:
  Hero::Shader* Shader;
  Hero::Mesh* Mesh;
  TransformComponent Transform;

public:
  Terrain(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;
};