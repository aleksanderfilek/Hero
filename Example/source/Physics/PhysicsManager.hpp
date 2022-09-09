#pragma once

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"

class PhysicsManager : public Hero::Actor
{
private:

public:
  PhysicsManager(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;
};