#pragma once 

#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Core/Sid.hpp"
#include "../Hero/Graphics/Color.hpp"

#include"../Utility/UniformBlock.hpp"
#include"../Components/Transform.hpp"

class DirectionalSun : public Hero::Actor
{
private:
  UniformBlock LightBuffer;
  TransformComponent Transform;

  Hero::ColorRGB CurrentColor;

public:
  DirectionalSun(const Hero::Sid& NewId);

  virtual void Start() override;
  virtual void Update() override;
  virtual void End() override;

  void SetColor(Hero::ColorRGB NewColor);
};