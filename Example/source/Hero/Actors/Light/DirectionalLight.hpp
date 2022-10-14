#pragma once 

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include "../../Graphics/Color.hpp"
#include"../../Graphics/UniformBlock.hpp"
#include"../../Components/Transform.hpp"

namespace Hero
{

class DirectionalLight : public Actor
{
public:
  UniformBlock LightBuffer;
  TransformComponent Transform;

  ColorRGB CurrentColor;

public:
  HERO DirectionalLight(const Sid& NewId);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void SetColor(ColorRGB NewColor);
};

}