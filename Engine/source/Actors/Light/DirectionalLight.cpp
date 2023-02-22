#include "DirectionalLight.hpp"

namespace Hero
{

HERO DirectionalLight::DirectionalLight(const Sid& Name)
 : Actor(Name)
{
  LightBuffer.Register<Float3>(SID("LightColor"));
  LightBuffer.Register<Float3>(SID("LightDirection"));
  LightBuffer.Apply(1);
}

HERO void DirectionalLight::Start()
{
  Actor::Start();

  SetColor(ColorRGB(255,255,255,255));

  Float3 forward = GetTransformRef()->GetWorldRotation().GetRightVector();
  LightBuffer.Set<Float3>(SID("LightDirection"), forward);
}

HERO void DirectionalLight::Update()
{
  Actor::Update();

  Float3 forward = GetTransformRef()->GetWorldRotation().GetRightVector();
  LightBuffer.Set<Float3>(SID("LightDirection"), forward);
}

HERO void DirectionalLight::End()
{
  Actor::End();
}

HERO void DirectionalLight::SetColor(ColorRGB NewColor)
{
  CurrentColor = NewColor;

  Float3 color = { 
    (float)CurrentColor.r/(float)255, 
    (float)CurrentColor.g/(float)255,
    (float)CurrentColor.b/(float)255
    };

  LightBuffer.Set<Float3>(SID("LightColor"), color);
}

}