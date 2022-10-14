#pragma once

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include "../../Components/Transform.hpp"
#include"../../Graphics/Cubemap.hpp"
#include <vector>

namespace Hero
{

class Skybox : public Actor
{
private:
  Cubemap* cubemap;
  class Material* material;
  std::vector<TransformComponent> transform;
  
public:
  HERO Skybox(const Sid& NewId);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void SetMaterial(class Material* Material);
  HERO void SetCubemap(Cubemap* Cubemap);
};

}