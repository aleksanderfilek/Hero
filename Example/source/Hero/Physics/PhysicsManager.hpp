#pragma once

#include "../Systems/ActorScene/Actor.hpp"
#include "../Core/Sid.hpp"

namespace Hero
{

class PhysicsManager : public Hero::Actor
{
private:

public:
  PhysicsManager(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;
};

}