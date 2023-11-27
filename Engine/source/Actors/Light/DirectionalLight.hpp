#pragma once 

#include "../../Systems/ActorScene/Actor.hpp"
#include "../../Core/Sid.hpp"
#include "../../Graphics/Color.hpp"
#include"../../Graphics/UniformBlock.hpp"

namespace Hero
{

class DirectionalLight : public Actor
{
public:
  UniformBlock LightBuffer;
  ColorRGB CurrentColor;

public:
  HERO DirectionalLight(const Sid& Name);

  HERO void Start() override;
  HERO void Update() override;
  HERO void End() override;

  HERO void SetColor(ColorRGB NewColor);
};

}