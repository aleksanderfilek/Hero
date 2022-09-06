#include "DirectionalSun.hpp"

DirectionalSun::DirectionalSun(const Hero::Sid& NewId) : Hero::Actor(NewId)
{
  LightBuffer.Register<Hero::Float3>(SID("LightColor"));
  LightBuffer.Register<Hero::Float3>(SID("LightPos"));
  LightBuffer.Apply(1);

  SetColor(Hero::ColorRGB(125,125,125,255));

  Hero::Float3 position = { 1.0f, 1.0f, 1.0f };
  LightBuffer.Set(SID("LightPos"), position);

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