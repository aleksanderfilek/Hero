#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Hero/Graphics/Cubemap.hpp"
#include "../Hero/Graphics/Shader.hpp"

class Cubemap : public Hero::Actor
{
private:
  Hero::Cubemap* cubemap;
  Hero::Shader* shader;
  
public:
  Cubemap(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;

};