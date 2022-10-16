#pragma once

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include"../../Graphics/Cubemap.hpp"

namespace Hero
{

class Skybox : public Actor
{
private:
  Cubemap* cubemap;
  class Material* material;
  
public:
  HERO Skybox(const Sid& Name);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void SetMaterial(class Material* Material);
  HERO void SetCubemap(Cubemap* Cubemap);
};

}