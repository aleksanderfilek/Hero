#include "DirectionalSun.hpp"

DirectionalSun::DirectionalSun(const Hero::Sid& NewId) : Hero::Actor(NewId)
{
  LightBuffer.Register<Hero::Float3>(SID("LightColor"));
  LightBuffer.Apply(1);

  CurrentColor = {255,255,255,255};
}

void DirectionalSun::Start()
{

}

void DirectionalSun::Update()
{

}

void DirectionalSun::End()
{

}

void DirectionalSun::SetColor(Hero::ColorRGB NewColor)
{
  CurrentColor = NewColor;

  Hero::Float3 color = { 
    (float)CurrentColor.r/(float)255, 
    (float)CurrentColor.g/(float)255,
    (float)CurrentColor.b/(float)255
    };

  LightBuffer.Set(SID("LightColor"), color);
}